ProcessTxVect(void)
{ int i,c,r,mask,key;

  mask=FFT.Size-1;

  for(i=0; i<2*WindowLen; i++) WindowBuff.Data[i].im=WindowBuff.Data[i].re=0.0;

  for(c=FirstDataCarr,i=0; i<DataCarriers; i+=2,c=(c+2*DataCarrSepar)&mask)
  { r=FFT.BitRevIdx[c];
    WindowBuff.Data[r].re=TxAmpl*FFT.Twiddle[TxVect[i]].re;
    WindowBuff.Data[r].im=(-TxAmpl)*FFT.Twiddle[TxVect[i]].im; }
  for(c=FirstDataCarr+DataCarrSepar,i=1; i<DataCarriers; i+=2,c=(c+2*DataCarrSepar)&mask)
  { r=WindowLen+FFT.BitRevIdx[c];
    WindowBuff.Data[r].re=TxAmpl*FFT.Twiddle[TxVect[i]].re;
    WindowBuff.Data[r].im=(-TxAmpl)*FFT.Twiddle[TxVect[i]].im; }


  if(CW_ID!=NULL)
  { key=CW_Coder.NextKey();
    if(key<0)
    { CW_Coder.SetTxMsg(CW_ID); key=key=CW_Coder.NextKey(); }
    if(key)
    { r=FFT.BitRevIdx[CW_Carr];
      WindowBuff.Data[r].re=CW_Ampl*FFT.Twiddle[CW_Phase].re;
      WindowBuff.Data[r].im=(-CW_Ampl)*FFT.Twiddle[CW_Phase].im;
      CW_Phase+=CW_PhaseCorr; CW_Phase&=mask;
      r=WindowLen+FFT.BitRevIdx[CW_Carr];
      WindowBuff.Data[r].re=CW_Ampl*FFT.Twiddle[CW_Phase].re;
      WindowBuff.Data[r].im=(-CW_Ampl)*FFT.Twiddle[CW_Phase].im;
      CW_Phase+=CW_PhaseCorr; CW_Phase&=mask;
    } else
    { CW_Phase+=2*CW_PhaseCorr; CW_Phase&=mask; }
  }


  FFT.CoreProc(WindowBuff.Data);
  FFT.CoreProc(WindowBuff.Data+WindowLen);

  for(i=0; i<2*WindowLen; i++) WindowBuff.Data[i].im*=(-1.0);


  Window.Process(&WindowBuff);


  Comb.Process(&Window.Output);


  return 0;
}
