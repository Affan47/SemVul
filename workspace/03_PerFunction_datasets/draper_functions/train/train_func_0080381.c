imProcessInterlaceSplit(const imImage* src_image, imImage* dst_image1, imImage* dst_image2)
{
  int i;
  int src_depth = src_image->has_alpha? src_image->depth+1: src_image->depth;

  for (i = 0; i < src_depth; i++)
  {
    switch(src_image->data_type)
    {
    case IM_BYTE:
      InterlaceSplit(src_image->width, src_image->height, (imbyte*)src_image->data[i],  (imbyte*)dst_image1->data[i], (imbyte*)dst_image2->data[i]);
      break;
    case IM_SHORT:
      InterlaceSplit(src_image->width, src_image->height, (short*)src_image->data[i],  (short*)dst_image1->data[i], (short*)dst_image2->data[i]);
      break;
    case IM_USHORT:
      InterlaceSplit(src_image->width, src_image->height, (imushort*)src_image->data[i],  (imushort*)dst_image1->data[i], (imushort*)dst_image2->data[i]);
      break;
    case IM_INT:
      InterlaceSplit(src_image->width, src_image->height, (int*)src_image->data[i],  (int*)dst_image1->data[i], (int*)dst_image2->data[i]);
      break;
    case IM_FLOAT:
      InterlaceSplit(src_image->width, src_image->height, (float*)src_image->data[i],  (float*)dst_image1->data[i], (float*)dst_image2->data[i]);
      break;
    case IM_CFLOAT:
      InterlaceSplit(src_image->width, src_image->height, (imcfloat*)src_image->data[i],  (imcfloat*)dst_image1->data[i], (imcfloat*)dst_image2->data[i]);
      break;
    }
  }
}
