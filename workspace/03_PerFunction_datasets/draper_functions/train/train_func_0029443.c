mgx11_setRGB(int r, int g, int b)
{
  int cell = colorlevels * colorlevels * colorlevels;

  if (!colorlevels)
    return (unsigned long)0;

  mgx11colorcells[cell].red = (unsigned short)(r * 256);
  mgx11colorcells[cell].green = (unsigned short)(g * 256);
  mgx11colorcells[cell].blue = (unsigned short)(b * 256);
  mgx11colorcells[cell].flags = DoRed | DoGreen | DoBlue;
  XStoreColor(mgx11display, cmap, &(mgx11colorcells[cell]));

  return mgx11colors[cell];
}
