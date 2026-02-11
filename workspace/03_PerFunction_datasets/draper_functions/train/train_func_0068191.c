processRGBA_Gray(imageStruct &image, imageStruct &right)
{
  int datasize = image.xsize * image.ysize;
  unsigned char *leftPix = image.data;
  unsigned char *rightPix = right.data;

  while(datasize--)	{
    unsigned int alpha = rightPix[chGray];
    leftPix[chRed] = INT_MULT(leftPix[chRed], alpha);
    leftPix[chGreen] = INT_MULT(leftPix[chGreen], alpha);
    leftPix[chBlue] = INT_MULT(leftPix[chBlue], alpha);
    leftPix += 4;
    rightPix++;
  }
}
