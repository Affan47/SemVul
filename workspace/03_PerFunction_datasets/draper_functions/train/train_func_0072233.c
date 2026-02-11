imImageSetBinary(imImage* image)
{
  assert(image);

  if (image->palette && image->data_type == IM_BYTE)
  {
    image->color_space = IM_BINARY;
    image->palette_count = 2;
    image->palette[0] = imColorEncode(0, 0, 0);
    image->palette[1] = imColorEncode(255, 255, 255);
  }
}
