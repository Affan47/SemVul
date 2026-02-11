Process(fcmpx *Data, int Time)
{ float nI,nQ; int i,p;
  Phase=(Phase+Time)&LenMask;
  for(p=i=0; i<Len; i++)
  { nI=Data[i].re*FreqTable[i].re-Data[i].im*FreqTable[i].im;
    nQ=Data[i].re*FreqTable[i].im+Data[i].im*FreqTable[i].re;
    Data[i].re=nI; Data[i].im=nQ;
    p=(p+Phase)&LenMask; }
  return 0;
}
