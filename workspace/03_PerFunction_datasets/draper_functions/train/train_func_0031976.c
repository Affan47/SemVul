SiS_ClearBuffer(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
   unsigned char  SISIOMEMTYPE *memaddr = SiS_Pr->VideoMemoryAddress;
   unsigned int   memsize = SiS_Pr->VideoMemorySize;
   unsigned short SISIOMEMTYPE *pBuffer;
   int i;

   if(!memaddr || !memsize) return;

   if(SiS_Pr->SiS_ModeType >= ModeEGA) {
      if(ModeNo > 0x13) {
	 memset_io(memaddr, 0, memsize);
      } else {
	 pBuffer = (unsigned short SISIOMEMTYPE *)memaddr;
	 for(i = 0; i < 0x4000; i++) writew(0x0000, &pBuffer[i]);
      }
   } else if(SiS_Pr->SiS_ModeType < ModeCGA) {
      pBuffer = (unsigned short SISIOMEMTYPE *)memaddr;
      for(i = 0; i < 0x4000; i++) writew(0x0720, &pBuffer[i]);
   } else {
      memset_io(memaddr, 0, 0x8000);
   }
}
