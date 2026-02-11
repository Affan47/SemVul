fontName(Font fid_)
{
  MSPrintFontData *data=(MSPrintFontData *)fontStruct(fid_);
  return data!=0?data->fontName().string():DefaultPrintFont;
}
