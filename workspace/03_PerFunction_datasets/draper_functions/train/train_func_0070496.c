FCEU_InitVirtualVideo(void)
{
 if(!XBuf)


 if(!(XBuf= (uint8*) (FCEU_malloc(256 * 256 + 8))))
  return 0;
 xbsave=XBuf;

 if(sizeof(uint8*)==4)
 {
  uint32 m;
  m=(uint32)XBuf;
  m=(4-m)&3;
  XBuf+=m;
 }
 memset(XBuf,128,256*256);
 return 1;
}
