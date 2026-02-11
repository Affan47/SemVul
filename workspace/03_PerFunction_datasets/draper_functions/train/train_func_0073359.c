ChangeTextOCR(
  const GUTF8String &value,
  const int width,
  const int height,
  const GP<DjVuFile> &dfile)
{
  if(value.length() && value.downcase() != "false")
  {
    const GP<ByteStream> bs=OCRcallback(value,DjVuImage::create(dfile));
    if( bs && bs->size() )
    {
      const GP<lt_XMLTags> tags(lt_XMLTags::create(bs));
      ChangeText(width,height,*dfile,*tags);
    }
  }
}
