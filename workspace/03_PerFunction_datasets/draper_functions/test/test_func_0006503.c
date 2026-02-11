DecodeImage(Image *image,unsigned char *pixels,
  const size_t length)
{
  int
    count,
    pixel;

  register long
    i;

  register unsigned char
    *p;

  p=pixels;
  while (p < (pixels+length))
  {
    pixel=ReadBlobByte(image);
    if (pixel <= 0x80)
      {
        count=pixel+1;
        for (i=0; i < count; i++)
          *p++=ReadBlobByte(image);
        continue;
      }
    count=pixel+1-0x80;
    pixel=ReadBlobByte(image);
    for (i=0; i < count; i++)
      *p++=(unsigned char) pixel;
  }
  return(True);
}
