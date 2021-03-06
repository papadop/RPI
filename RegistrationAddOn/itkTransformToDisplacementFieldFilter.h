/*=========================================================================

Program:   vtkINRIA3D
Module:    $Id: CodeCopyright.txt 1182 2009-06-30 09:19:05Z acanale $
Language:  C++
Author:    $Author: $
Date:      $Date: 2009-06-30 11:19:05 +0200 (mar, 30 jun 2009) $
Version:   $Revision: 1182 $

Copyright (c) 2007 INRIA - Asclepios Project. All rights reserved.
See Copyright.txt for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __itkTransformToDisplacementFieldFilter_h
#define __itkTransformToDisplacementFieldFilter_h

#include "itkImageSource.h"
#include "itkKernelTransform.h"
#include "itkImageRegionIteratorWithIndex.h"

namespace itk
{

/** \class TransformToDisplacementFieldFilter
 * \brief Computes a deformation field from an input spatial transformation.
 *
 * TransformToDisplacementFieldFilter produces a deformation field from an input
 * spatial transformation.
 * 
 * This source object expects the image to be of pixel type Vector.
 *
 * \author Tom Vercauteren, INRIA & Mauna Kea Technologies
 *
 * \ingroup ImageSource
 */
template <class TOutputImage, class TTransformScalarType=double>
class ITK_EXPORT TransformToDisplacementFieldFilter:
  public ImageSource<TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef TransformToDisplacementFieldFilter         Self;
  typedef ImageSource<TOutputImage>      Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;
  
  typedef TOutputImage OutputImageType;
  typedef typename OutputImageType::Pointer     OutputImagePointer;
  typedef typename OutputImageType::RegionType  OutputImageRegionType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);  

  /** Run-time type information (and related methods). */
  itkTypeMacro(TransformToDisplacementFieldFilter, ImageToImageFilter);

  /** Number of dimensions. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

  /** Transform typedef.*/
  typedef TTransformScalarType TransformScalarType;
  typedef itk::Transform<
    TransformScalarType,ImageDimension,ImageDimension> TransformType;
  typedef  typename TransformType::Pointer         TransformPointer;
  


  /** Image size typedef. */
  typedef typename OutputImageType::SizeType      OutputSizeType;

  /** Image index typedef. */
  typedef typename OutputImageType::IndexType     OutputIndexType;

  /** Image pixel value typedef. */
  typedef typename TOutputImage::PixelType        OutputPixelType;
  typedef typename OutputPixelType::ValueType     OutputPixelComponentType;

  itkStaticConstMacro(PixelDimension, unsigned int,
                      OutputPixelType::Dimension );

  /** Image spacing typedef */
  typedef typename TOutputImage::SpacingType      SpacingType;
  typedef typename TOutputImage::PointType        OriginPointType;
  typedef typename TOutputImage::DirectionType    DirectionType;
  
  /** Set/Get the Transfrom. */
  itkSetObjectMacro( Transform, TransformType );
  itkGetObjectMacro( Transform, TransformType );

  /** Set the size of the output image. */
  itkSetMacro( OutputRegion, OutputImageRegionType );

  /** Get the size of the output image. */
  itkGetConstReferenceMacro( OutputRegion, OutputImageRegionType );
     
  /** Set the output image spacing. */
  itkSetMacro(OutputSpacing, SpacingType);
  virtual void SetOutputSpacing( const double* values);

  /** Get the output image spacing. */
  itkGetConstReferenceMacro( OutputSpacing, SpacingType );

  /** Set the output image origin. */
  itkSetMacro(OutputOrigin, OriginPointType);
  virtual void SetOutputOrigin( const double* values);

  /** Get the output image origin. */
  itkGetConstReferenceMacro( OutputOrigin, OriginPointType );


  /** Set the output image spacing. */
  itkSetMacro(OutputDirection, DirectionType);

  /** Get the output image spacing. */
  itkGetConstReferenceMacro( OutputDirection, DirectionType );

  
  /** TransformToDisplacementFieldFilter produces an image which is a different size
   * than its input.  As such, it needs to provide an implementation
   * for GenerateOutputInformation() in order to inform the pipeline
   * execution model.  The original documentation of this method is
   * below. \sa ProcessObject::GenerateOutputInformaton() */
  virtual void GenerateOutputInformation();

  /** Method Compute the Modified Time based on changed to the components. */
  unsigned long GetMTime( void ) const;

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(SameDimensionCheck,
    (Concept::SameDimension<ImageDimension,PixelDimension>));
  itkConceptMacro(DisplacementFieldHasNumericTraitsCheck,
    (Concept::HasNumericTraits<typename TOutputImage::PixelType::ValueType>));
  /** End concept checking */
#endif

protected:
  TransformToDisplacementFieldFilter();
  ~TransformToDisplacementFieldFilter() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** 
   * GenerateData() computes the deformation field.
   */
  void GenerateData();

private:
  TransformToDisplacementFieldFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  TransformPointer              m_Transform;   // Coordinate transform to use

  OutputImageRegionType         m_OutputRegion;      // Region of the output image
  SpacingType                   m_OutputSpacing;     // output image spacing
  OriginPointType               m_OutputOrigin;      // output image origin
  DirectionType                 m_OutputDirection;
};

  
} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkTransformToDisplacementFieldFilter.txx"
#endif
  
#endif
