flFreeFontInfo(FLfontStruct *fontStruct)
{
  TRACE(("flFreeFontInfo\n"));

  if (fontStruct) {
    if (fontStruct->properties) free(fontStruct->properties);
    if (fontStruct->per_char)   free(fontStruct->per_char);

    free(fontStruct);
  }
}
