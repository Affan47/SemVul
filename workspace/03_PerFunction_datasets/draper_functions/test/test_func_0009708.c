imImageSetAlpha(imImage* image, float alpha)
{
  assert(image);

  if (image->has_alpha)
  {
    switch(image->data_type)
    {
    case IM_BYTE:
      memset(image->data[image->depth], (imbyte)alpha, image->plane_size);
      break;
    case IM_SHORT:
      iSet((short*)image->data[image->depth], (short)alpha, image->plane_size);
      break;
    case IM_USHORT:
      iSet((imushort*)image->data[image->depth], (imushort)alpha, image->plane_size);
      break;
    case IM_INT:
      iSet((int*)image->data[image->depth], (int)alpha, image->plane_size);
      break;
    case IM_FLOAT:
      iSet((float*)image->data[image->depth], (float)alpha, image->plane_size);
      break;
    }
  }
}
