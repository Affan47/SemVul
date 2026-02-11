ComputeTextureSize(
  const int extent[6], int &xdim, int &ydim,
  int imageSize[2], int textureSize[2])
{


  xdim = 1;
  ydim = 2;
  if (extent[0] != extent[1])
    {
    xdim = 0;
    if (extent[2] != extent[3])
      {
      ydim = 1;
      }
    }


  imageSize[0] = (extent[xdim*2+1] - extent[xdim*2] + 1);
  imageSize[1] = (extent[ydim*2+1] - extent[ydim*2] + 1);

  textureSize[0] = imageSize[0];
  textureSize[1] = imageSize[1];
}
