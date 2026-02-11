imProcessReduce(const imImage* src_image, imImage* dst_image, int order)
{
  int ret = 0;
  int counter = imProcessCounterBegin("Reduce Size");
  const char* int_msg = (order == 1)? "Bilinear Decimation": "Zero Order Decimation";
  int src_depth = src_image->has_alpha? src_image->depth+1: src_image->depth;
  imCounterTotal(counter, src_depth*dst_image->height, int_msg);

  for (int i = 0; i < src_depth; i++)
  {
    switch(src_image->data_type)
    {
    case IM_BYTE:
      ret = iReduce(src_image->width, src_image->height, (const imbyte*)src_image->data[i],
                    dst_image->width, dst_image->height, (imbyte*)dst_image->data[i],
                    float(0), order, counter);
      break;
    case IM_SHORT:
      ret = iReduce(src_image->width, src_image->height, (const short*)src_image->data[i],
                    dst_image->width, dst_image->height, (short*)dst_image->data[i],
                    float(0), order, counter);
      break;
    case IM_USHORT:
      ret = iReduce(src_image->width, src_image->height, (const imushort*)src_image->data[i],
                    dst_image->width, dst_image->height, (imushort*)dst_image->data[i],
                    float(0), order, counter);
      break;
    case IM_INT:
      ret = iReduce(src_image->width, src_image->height, (const int*)src_image->data[i],
                    dst_image->width, dst_image->height, (int*)dst_image->data[i],
                    float(0), order, counter);
      break;
    case IM_FLOAT:
      ret = iReduce(src_image->width, src_image->height, (const float*)src_image->data[i],
                    dst_image->width, dst_image->height, (float*)dst_image->data[i],
                    float(0), order, counter);
      break;
    case IM_CFLOAT:
      ret = iReduce(src_image->width, src_image->height, (const imcfloat*)src_image->data[i],
                    dst_image->width, dst_image->height, (imcfloat*)dst_image->data[i],
                    imcfloat(0,0), order, counter);
      break;
    }
  }

  imProcessCounterEnd(counter);
  return ret;
}
