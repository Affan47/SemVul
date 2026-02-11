RDoPCM(void)
{
 int32 V;

 for(V=ChannelBC[4];V<SOUNDTS;V++)
  WaveHi[V]+=RawDALatch<<16;

 ChannelBC[4]=SOUNDTS;
}
