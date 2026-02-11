Synco(void)
{
 uint32 x;
 if(mapbyte1[0]<=2)
  MIRROR_SET2(1);
 else
  MIRROR_SET2(0);
 for(x=0x6000;x<0x10000;x+=8192)
  ROM_BANK8(x,Get8K(x));
}
