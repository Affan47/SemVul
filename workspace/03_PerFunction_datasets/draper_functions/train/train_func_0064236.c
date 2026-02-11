SubWrite(FILE *st, SFORMAT *sf)
{
 uint32 acc=0;

 while(sf->v)
 {
  if(sf->s==~0)
  {
   uint32 tmp;

   if(!(tmp=SubWrite(st,(SFORMAT *)sf->v)))
    return(0);
   acc+=tmp;
   sf++;
   continue;
  }

  acc+=8;
  acc+=sf->s&(~RLSB);

  if(st)
  {
   fwrite(sf->desc,1,4,st);
   write32le(sf->s&(~RLSB),st);

   #ifndef LSB_FIRST
   if(sf->s&RLSB)
    FlipByteOrder(sf->v,sf->s&(~RLSB));
   #endif

   fwrite((uint8 *)sf->v,1,sf->s&(~RLSB),st);

   #ifndef LSB_FIRST
   if(sf->s&RLSB)
    FlipByteOrder(sf->v,sf->s&(~RLSB));
   #endif
  }
  sf++;
 }

 return(acc);
}
