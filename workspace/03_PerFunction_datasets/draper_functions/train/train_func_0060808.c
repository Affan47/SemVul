Pete_MetaImage_GetAreaAverage(U32* pImage,int nLeftX,int nTopY,int nRightX,int nBottomY,int nStride) {


  const int nXDelta=nRightX-nLeftX;
  const int nYDelta=nBottomY-nTopY;

  if ((nXDelta<=0)||(nYDelta<=0))return 0x00000000;

  U32* pCurrentImage=pImage+(nTopY*nWidth)+nLeftX;
  U32*const pImageEnd=(pCurrentImage+(nYDelta*nWidth)+nXDelta);

  int nRedTotal=0;
  int nGreenTotal=0;
  int nBlueTotal=0;
  int nAlphaTotal=0;

  int nSampleCount=0;

  while (pCurrentImage<pImageEnd) {
    U32*const pImageLineStart=pCurrentImage;
    U32*const pImageLineEnd=pCurrentImage+nXDelta;

    while (pCurrentImage<pImageLineEnd) {
      const U32 ImageColour=*pCurrentImage;

      const U32 nImageRed=(ImageColour>>SHIFT_RED)&0xff;
      const U32 nImageGreen=(ImageColour>>SHIFT_GREEN)&0xff;
      const U32 nImageBlue=(ImageColour>>SHIFT_BLUE)&0xff;
      const U32 nImageAlpha=(ImageColour>>SHIFT_ALPHA)&0xff;

      nRedTotal+=nImageRed;
      nGreenTotal+=nImageGreen;
      nBlueTotal+=nImageBlue;
      nAlphaTotal+=nImageAlpha;

      nSampleCount+=1;

      pCurrentImage+=nStride;
    }

    pCurrentImage=pImageLineStart+(nStride*nWidth);
  }

  const int nAverageRed=(nRedTotal/nSampleCount);
  const int nAverageGreen=(nGreenTotal/nSampleCount);
  const int nAverageBlue=(nBlueTotal/nSampleCount);
  const int nAverageAlpha=(nAlphaTotal/nSampleCount);


  U32 Average=
    (nAverageRed<<SHIFT_RED)|
    (nAverageGreen<<SHIFT_GREEN)|
    (nAverageBlue<<SHIFT_BLUE)|
    (nAverageAlpha<<SHIFT_ALPHA);

  return Average;
}
