imProcessSwirl(const imImage* src_image, imImage* dst_image, float k, int order)
{
  int ret = 0;

  int counter = imProcessCounterBegin("Swirl Distort");
  int src_depth = src_image->has_alpha? src_image->depth+1: src_image->depth;
  imCounterTotal(counter, src_depth*dst_image->height, "Processing...");

  for (int i = 0; i < src_depth; i++)
  {
    switch(src_image->data_type)
    {
    case IM_BYTE:
      ret = Swirl(src_image->width, src_image->height, (imbyte*)src_image->data[i], (imbyte*)dst_image->data[i], k, counter, float(0), order);
      break;
    case IM_SHORT:
      ret = Swirl(src_image->width, src_image->height, (short*)src_image->data[i], (short*)dst_image->data[i], k, counter, float(0), order);
      break;
    case IM_USHORT:
      ret = Swirl(src_image->width, src_image->height, (imushort*)src_image->data[i], (imushort*)dst_image->data[i], k, counter, float(0), order);
      break;
    case IM_INT:
      ret = Swirl(src_image->width, src_image->height, (int*)src_image->data[i], (int*)dst_image->data[i], k, counter, float(0), order);
      break;
    case IM_FLOAT:
      ret = Swirl(src_image->width, src_image->height, (float*)src_image->data[i], (float*)dst_image->data[i], k, counter, float(0), order);
      break;
    case IM_CFLOAT:
      ret = Swirl(src_image->width, src_image->height, (imcfloat*)src_image->data[i], (imcfloat*)dst_image->data[i], k, counter, imcfloat(0,0), order);
      break;
    }

    if (!ret)
      break;
  }

  imProcessCounterEnd(counter);

  return ret;
}
