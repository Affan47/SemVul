DoAYSQ(int x)
{
    int32 freq=((MapperExRAM[x<<1]|((MapperExRAM[(x<<1)+1]&15)<<8))+1)<<(4+17);
    int32 amp=(MapperExRAM[0x8+x]&15)<<2;
    int32 start,end;
    int V;

    amp+=amp>>1;

    start=CAYBC[x];
    end=(SOUNDTS<<16)/soundtsinc;
    if(end<=start) return;
    CAYBC[x]=end;

    if(amp)
    for(V=start;V<end;V++)
    {
     if(dcount[x])
      Wave[V>>4]+=amp;
     vcount[x]-=nesincsize;
     while(vcount[x]<=0)
     {
      dcount[x]^=1;
      vcount[x]+=freq;
     }
    }
}
