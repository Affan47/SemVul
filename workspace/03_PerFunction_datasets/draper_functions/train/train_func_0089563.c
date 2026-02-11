imPaletteHotIron(void)
{
  long* palette = (long*)malloc(sizeof(long)*256);
  long* ct = palette;
  int lIndex, lSubIndex;

  for (lIndex = 0, lSubIndex = 0; lSubIndex < 128; lSubIndex++, lIndex += 2)
  {


    *(ct++) = imColorEncode((imbyte)lIndex, 0, 0);
  }

  for (lIndex = 0, lSubIndex = 0; lSubIndex < 64; lSubIndex++, lIndex += 2)
  {


    *(ct++) = imColorEncode(255, (imbyte)lIndex, 0);
  }

  for (lIndex = 0, lSubIndex = 0; lSubIndex < 63; lSubIndex++, lIndex += 2)
  {


    imbyte red = 255;
    imbyte green = (imbyte)(128 + lIndex);
    imbyte blue = (imbyte)(lIndex * 2 + 4);

    *(ct++) = imColorEncode(red, green, blue);
  }

  *(ct++) = imColorEncode(255, 255, 255);

  return palette;
}
