matchesPresentationLUT(DVPSPrintPresentationLUTAlignment align) const
{
  OFBool result = OFFalse;
  switch (align)
  {
    case DVPSK_shape:
      result = OFTrue;
      break;
    case DVPSK_table8:
      if (imageDepth != DVPSN_12bit) result = OFTrue;
      break;
    case DVPSK_table12:
      if (imageDepth != DVPSN_8bit) result = OFTrue;
      break;
    case DVPSK_other:
      break;
  }
  return result;
}
