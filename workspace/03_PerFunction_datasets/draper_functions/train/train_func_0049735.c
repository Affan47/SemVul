GenerateStreamableReadRegionFromRequestedRegion(
  const ImageIORegion & requested) const
{


  unsigned int minIODimension = this->m_NumberOfDimensions;

  while ( minIODimension )
    {
    if ( this->m_Dimensions[minIODimension - 1] == 1 )
      {
      --minIODimension;
      }
    else
      {
      break;
      }
    }


  unsigned int maxDimension =
    minIODimension > requested.GetImageDimension() ? minIODimension : requested.GetImageDimension();


  ImageIORegion streamableRegion(maxDimension);


  for ( unsigned int i = 0; i < minIODimension; i++ )
    {
    streamableRegion.SetSize(i, this->m_Dimensions[i]);
    streamableRegion.SetIndex(i, 0);
    }


  for ( unsigned int j = minIODimension; j < streamableRegion.GetImageDimension(); j++ )
    {
    streamableRegion.SetSize(j, 1);
    streamableRegion.SetIndex(j, 0);
    }


  return streamableRegion;
}
