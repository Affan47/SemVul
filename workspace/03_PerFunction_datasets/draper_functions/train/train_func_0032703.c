Preset(int size, int step, float *window)
{ int err,i;

  Size=size; SizeMask=Size-1;
  err=FFT.Preset(Size); if(err) goto Error;

  if(!ExternWindow) { free(Window); ExternWindow=1; }
  Window=window;

  err=ReallocArray(&FFTbuff,Size); if(err) goto Error;

  err=ReallocArray(&SlideBuff,Size); if(err) goto Error;
  for(i=0; i<Size; i++) SlideBuff[i]=0.0;
  SlidePtr=0; Slide=0; Dist=step; Left=Dist;

  return 0;

  Error: Free(); return -1;
}
