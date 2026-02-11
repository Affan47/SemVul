SiS_SetCRTCRegs(struct SiS_Private *SiS_Pr, unsigned short StandTableIndex)
{
   unsigned char  CRTCdata;
   unsigned short i;


   SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

   for(i = 0; i <= 0x18; i++) {
      CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
      SiS_SetReg(SiS_Pr->SiS_P3d4,i,CRTCdata);
   }

   if(SiS_Pr->ChipType >= SIS_661) {
      SiS_OpenCRTC(SiS_Pr);
      for(i = 0x13; i <= 0x14; i++) {
	 CRTCdata = SiS_Pr->SiS_StandTable[StandTableIndex].CRTC[i];
	 SiS_SetReg(SiS_Pr->SiS_P3d4,i,CRTCdata);
      }
   } else if( ( (SiS_Pr->ChipType == SIS_630) ||
	        (SiS_Pr->ChipType == SIS_730) )  &&
	      (SiS_Pr->ChipRevision >= 0x30) ) {
      if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
	 if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToTV)) {
	    SiS_SetReg(SiS_Pr->SiS_P3d4,0x18,0xFE);
	 }
      }
   }
}
