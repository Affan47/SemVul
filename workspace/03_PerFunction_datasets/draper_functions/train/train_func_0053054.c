PushFrontRegionBorder(KLMSegmentationBorder *pBorderCandidate)
{
  if ( pBorderCandidate == NULL )
    {
    itkExceptionMacro(<< "Null pointer to segmentation region border");
    }
  m_RegionBorderVector.insert(m_RegionBorderVector.begin(), pBorderCandidate);
}
