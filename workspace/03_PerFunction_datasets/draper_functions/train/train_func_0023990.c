imCalcHistogram(const imImage* src_image, unsigned long* histo, int plane, int cumulative)
{
  switch (src_image->data_type)
  {
  case IM_BYTE:
    imCalcByteHistogram((imbyte*)src_image->data[plane], src_image->count, histo, cumulative);
    break;
  case IM_SHORT:
    imCalcShortHistogram((short*)src_image->data[plane], src_image->count, histo, cumulative);
    break;
  case IM_USHORT:
    imCalcUShortHistogram((imushort*)src_image->data[plane], src_image->count, histo, cumulative);
    break;
  }
}
