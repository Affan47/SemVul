imPaletteUniform(void)
{
  long* palette = (long*)malloc(sizeof(long)*256);
  long* ct = palette;

  for (int lRedIndex = 0; lRedIndex < 6; lRedIndex++)
    for (int lGreenIndex = 0; lGreenIndex < 6; lGreenIndex++)
      for (int lBlueIndex = 0; lBlueIndex < 6; lBlueIndex++)
      {
        imbyte red = (imbyte)iSixStepsTable[lRedIndex];
        imbyte green = (imbyte)iSixStepsTable[lGreenIndex];
        imbyte blue = (imbyte)iSixStepsTable[lBlueIndex];

        *(ct++) = imColorEncode(red, green, blue);
      }


  for (int lIndex = 6; lIndex < 246; lIndex += 6)
  {
    *(ct++) = imColorEncode((imbyte)lIndex, (imbyte)lIndex, (imbyte)lIndex);
  }

  return palette;
}
