RDoTriangle(void)
{
 int32 V;
 int32 tcout;

 tcout=(tristep&0xF);
 if(!(tristep&0x10)) tcout^=0xF;
 tcout=(tcout*3) << 16;

 if(!lengthcount[2] || !TriCount)
 {
  int32 *start = &WaveHi[ChannelBC[2]];
  int32 count = SOUNDTS - ChannelBC[2];
  while(count--)
  {
   *start += tcout;
   start++;
  }


 }
 else
  for(V=ChannelBC[2];V<SOUNDTS;V++)
  {
    WaveHi[V]+=tcout;
    wlcount[2]--;
    if(!wlcount[2])
    {
     wlcount[2]=(PSG[0xa]|((PSG[0xb]&7)<<8))+1;
     tristep++;
     tcout=(tristep&0xF);
     if(!(tristep&0x10)) tcout^=0xF;
     tcout=(tcout*3) << 16;
    }
  }

 ChannelBC[2]=SOUNDTS;
}
