imProcessAbnormalHyperionCorrection(const imImage* src_image, imImage* dst_image, int threshold_consecutive, int threshold_percent, imImage* image_abnormal)
{
  imImage* abnormal = image_abnormal;
  if (!image_abnormal)
    abnormal = imImageCreateBased(src_image, 0, 0, IM_BINARY, IM_BYTE);

  switch(src_image->data_type)
  {
  case IM_BYTE:
    DoAbnormalCorrection((imbyte*)src_image->data[0], (imbyte*)dst_image->data[0], src_image->width, src_image->height, (imbyte*)abnormal->data[0], threshold_consecutive, threshold_percent);
    break;
  case IM_SHORT:
    DoAbnormalCorrection((short*)src_image->data[0], (short*)dst_image->data[0], src_image->width, src_image->height, (imbyte*)abnormal->data[0], threshold_consecutive, threshold_percent);
    break;
  case IM_USHORT:
    DoAbnormalCorrection((imushort*)src_image->data[0], (imushort*)dst_image->data[0], src_image->width, src_image->height, (imbyte*)abnormal->data[0], threshold_consecutive, threshold_percent);
    break;
  case IM_INT:
    DoAbnormalCorrection((int*)src_image->data[0], (int*)dst_image->data[0], src_image->width, src_image->height, (imbyte*)abnormal->data[0], threshold_consecutive, threshold_percent);
    break;
  case IM_FLOAT:
    DoAbnormalCorrection((float*)src_image->data[0], (float*)dst_image->data[0], src_image->width, src_image->height, (imbyte*)abnormal->data[0], threshold_consecutive, threshold_percent);
    break;
  }

  if (!image_abnormal)
    imImageDestroy(abnormal);
}
