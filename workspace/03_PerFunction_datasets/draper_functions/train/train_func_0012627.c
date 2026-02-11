SetSoundVariables(void)
{
  int x;

  fhinc=PAL?16626:14915;
  fhinc*=24;

  if(FSettings.SndRate)
  {
   wlookup1[0]=0;
   for(x=1;x<32;x++)
   {
    wlookup1[x]=(double)16*16*16*4*95.52/((double)8128/(double)x+100);
    if(!FSettings.soundq) wlookup1[x]>>=4;
   }
   wlookup2[0]=0;
   for(x=1;x<203;x++)
   {
    wlookup2[x]=(double)16*16*16*4*163.67/((double)24329/(double)x+100);
    if(!FSettings.soundq) wlookup2[x]>>=4;
   }
   if(FSettings.soundq>=1)
   {
    DoNoise=RDoNoise;
    DoTriangle=RDoTriangle;
    DoPCM=RDoPCM;
    DoSQ1=RDoSQ1;
    DoSQ2=RDoSQ2;
   }
   else
   {
    DoNoise=DoTriangle=DoPCM=DoSQ1=DoSQ2=Dummyfunc;
    DoSQ1=RDoSQLQ;
    DoSQ2=RDoSQLQ;
    DoTriangle=RDoTriangleNoisePCMLQ;
    DoNoise=RDoTriangleNoisePCMLQ;
    DoPCM=RDoTriangleNoisePCMLQ;
   }
  }
  else
  {
   DoNoise=DoTriangle=DoPCM=DoSQ1=DoSQ2=Dummyfunc;
   return;
  }

  MakeFilters(FSettings.SndRate);

  if(GameExpSound.RChange)
   GameExpSound.RChange();

  nesincsize=(int64)(((int64)1<<17)*(double)(PAL?PAL_CPU:NTSC_CPU)/(FSettings.SndRate * 16));
  memset(sqacc,0,sizeof(sqacc));
  memset(ChannelBC,0,sizeof(ChannelBC));

  LoadDMCPeriod(DMCFormat&0xF);

  soundtsinc=(uint32)((uint64)(PAL?(long double)PAL_CPU*65536:(long double)NTSC_CPU*65536)/(FSettings.SndRate * 16));
}
