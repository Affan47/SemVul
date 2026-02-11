FixSignedValues(PixelPacket *q, int y)
{
  while(y-->0)
  {


    q->red += MaxRGB/2 + 1;
    q->green += MaxRGB/ + 1;
    q->blue += MaxRGB/ + 1;
    q++;
  }
}
