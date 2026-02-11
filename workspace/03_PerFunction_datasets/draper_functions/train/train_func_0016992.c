ShrinkSourceImageFastYUV(U32* pSource, U32* pOutput, float SubWidth,float SubHeight)
{
  if (SubWidth>static_cast<float>(nWidth))  SubWidth=static_cast<float>(nWidth);
  if (SubHeight>static_cast<float>(nHeight))SubHeight=static_cast<float>(nHeight);

  const float SourceYInc=(nHeight/SubHeight);
  const float SourceXInc=(nWidth/SubWidth);

  int nUTotal=0;
  int nYTotal=0;
  int nVTotal=0;

  int nSampleCount=0;

  U32* pCurrentOutput=pOutput;

  float SourceY;
  for (SourceY=0.0f; SourceY<nHeight; SourceY+=SourceYInc) {
    U32* pOutputLineStart=pCurrentOutput;
    const int nTopY=static_cast<int>(SourceY);
    U32* pSourceLineStart=pSource+(nTopY*nWidth);

    float SourceX;
    for (SourceX=0.0f; SourceX<nWidth; SourceX+=SourceXInc) {
      const int nLeftX=static_cast<int>(SourceX);
      const U32 OutputColour=*(pSourceLineStart+nLeftX);
      const U32 nOutputU =(OutputColour>>SHIFT_U )&0xff;
      const U32 nOutputY1=(OutputColour>>SHIFT_Y1)&0xff;
      const U32 nOutputV =(OutputColour>>SHIFT_V )&0xff;
      const U32 nOutputY2=(OutputColour>>SHIFT_Y2)&0xff;

      nUTotal+=nOutputU;
      nYTotal+=nOutputY1;
      nVTotal+=nOutputV;
      nYTotal+=nOutputY2;

      nSampleCount+=1;
      *pCurrentOutput=OutputColour;
      pCurrentOutput+=1;
    }
    pCurrentOutput=pOutputLineStart+nWidth;
  }

  const unsigned char nAverageY=(nYTotal/(nSampleCount<<1));
  const unsigned char nAverageU=(nUTotal/nSampleCount);
  const unsigned char nAverageV=(nVTotal/nSampleCount);

  U32 Average=
    (nAverageU<<SHIFT_U )|
    (nAverageY<<SHIFT_Y1)|
    (nAverageV<<SHIFT_V )|
    (nAverageY<<SHIFT_Y2);

  return Average;
}
