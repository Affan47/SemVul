Process(float *data)
{ int s,i,k; float Min,Max,Sig,Noise,SNR; int MinPos,MaxPos,code;

  CopyArray(IntlvPipe+IntlvPtr,data,ScanSize);


  for(s=0; s<ScanLen; s++)
  {
    for(i=0; i<DataCarriers; i++)
    { k=IntlvPtr-ScanSize-IntlvPatt[i]; if(k<0) k+=IntlvSize;
      if((s&1)&&(i&1)) { k+=ScanSize; if(k>=IntlvSize) k-=IntlvSize; }
      WalshBuff[i]=IntlvPipe[k+s+i];
    }
    WalshTrans(WalshBuff,DataCarriers);
    Min=FindMin(WalshBuff,DataCarriers,MinPos);
    Max=FindMax(WalshBuff,DataCarriers,MaxPos);
    if(fabs(Max)>fabs(Min))
    { code=MaxPos+DataCarriers;
      Sig=fabs(Max); WalshBuff[MaxPos]=0.0; }
    else
    { code=MinPos;
      Sig=fabs(Min); WalshBuff[MinPos]=0.0; }
    Noise=RMS(WalshBuff,DataCarriers);
    if(Noise>0.0) SNR=Sig/Noise; else SNR=0.0;
    LowPass2(SNR,DecodeSnrMid[s],DecodeSnrOut[s],W1,W2,W5);


    DecodePipe[DecodePtr+s]=code;
  }
  IntlvPtr+=ScanSize; if(IntlvPtr>=IntlvSize) IntlvPtr=0;
  DecodePtr+=ScanLen; if(DecodePtr>=DecodeSize) DecodePtr=0;
  Max=FindMax(DecodeSnrOut,ScanLen,MaxPos);
  Output=DecodePipe[DecodePtr+MaxPos];
  SignalToNoise=Max; CarrOfs=MaxPos-(ScanLen-1)/2;


  return 0;
}
