Preset(int size, int step,
      void (*proc)(fcmpx *Spectra, int Len), float *window)
{ int err,i;

  Size=size; SizeMask=Size-1;
  err=FFT.Preset(Size); if(err) goto Error;

  if(!ExternWindow) { free(Window); ExternWindow=1; }
  Window=window;

  ReallocArray(&FFTbuff,Size); if(err) goto Error;

  for(i=0; i<2; i++)
  { err=ReallocArray(&Spectr[i],Size/2); if(err) goto Error; }

  err=ReallocArray(&SlideBuff,Size); if(err) goto Error;
  for(i=0; i<Size; i++) SlideBuff[i]=0.0;
  SlidePtr=0; Slide=0; Dist=step; Left=Dist;

  err=ReallocArray(&OvlapBuff,Size); if(err) goto Error;
  for(i=0; i<Size; i++) OvlapBuff[i]=0.0; OvlapPtr=0;

  SpectraProc=proc;

  return 0;

  Error: Free(); return -1;
}
