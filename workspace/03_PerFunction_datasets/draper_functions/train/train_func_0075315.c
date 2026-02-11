SiS_CR36BIOSWord23b(struct SiS_Private *SiS_Pr)
{
   unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
   unsigned short temp,temp1;

   if(SiS_Pr->SiS_UseROM) {
      if((ROMAddr[0x233] == 0x12) && (ROMAddr[0x234] == 0x34)) {
	 temp = 1 << ((SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4) & 0x0f);
	 temp1 = SISGETROMW(0x23b);
	 if(temp1 & temp) return true;
      }
   }
   return false;
}
