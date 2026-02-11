SiSDetermineROMUsage(struct SiS_Private *SiS_Pr)
{
   unsigned char  *ROMAddr  = SiS_Pr->VirtualRomBase;
   unsigned short romptr = 0;

   SiS_Pr->SiS_UseROM = false;
   SiS_Pr->SiS_ROMNew = false;
   SiS_Pr->SiS_PWDOffset = 0;

   if(SiS_Pr->ChipType >= XGI_20) return;

   if((ROMAddr) && (SiS_Pr->UseROM)) {
      if(SiS_Pr->ChipType == SIS_300) {


	 if((ROMAddr[3] == 0xe9) && ((ROMAddr[5] << 8) | ROMAddr[4]) > 0x21a)
	    SiS_Pr->SiS_UseROM = true;
      } else if(SiS_Pr->ChipType < SIS_315H) {


	 SiS_Pr->SiS_UseROM = true;
      } else {

	 SiS_Pr->SiS_UseROM = true;
	 if((SiS_Pr->SiS_ROMNew = SiSDetermineROMLayout661(SiS_Pr))) {
	    SiS_Pr->SiS_EMIOffset = 14;
	    SiS_Pr->SiS_PWDOffset = 17;
	    SiS_Pr->SiS661LCD2TableSize = 36;

	    if((romptr = SISGETROMW(0x0102))) {
	       if(ROMAddr[romptr + (32 * 16)] == 0xff)
		  SiS_Pr->SiS661LCD2TableSize = 32;
	       else if(ROMAddr[romptr + (34 * 16)] == 0xff)
		  SiS_Pr->SiS661LCD2TableSize = 34;
	       else if(ROMAddr[romptr + (36 * 16)] == 0xff)
		  SiS_Pr->SiS661LCD2TableSize = 36;
	       else if( (ROMAddr[romptr + (38 * 16)] == 0xff) ||
		 	(ROMAddr[0x6F] & 0x01) ) {
		  SiS_Pr->SiS661LCD2TableSize = 38;
		  SiS_Pr->SiS_EMIOffset = 16;
		  SiS_Pr->SiS_PWDOffset = 19;
	       }
	    }
	 }
      }
   }
}
