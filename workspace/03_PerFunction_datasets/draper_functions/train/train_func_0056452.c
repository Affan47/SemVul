SiS_OEM310Setting(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex, unsigned short RRTI)
{
   if((SiS_Pr->SiS_ROMNew) && (SiS_Pr->SiS_VBType & VB_SISLVDS)) {
      SetDelayComp661(SiS_Pr, ModeNo, ModeIdIndex, RRTI);
      if(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) {
         SetCRT2SyncDither661(SiS_Pr, ModeNo, RRTI);
         SetPanelParms661(SiS_Pr);
      }
   } else {
      SetDelayComp(SiS_Pr,ModeNo);
   }

   if((SiS_Pr->SiS_VBType & VB_SISVB) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) {
      SetAntiFlicker(SiS_Pr,ModeNo,ModeIdIndex);
      SetPhaseIncr(SiS_Pr,ModeNo,ModeIdIndex);
      SetYFilter(SiS_Pr,ModeNo,ModeIdIndex);
      if(SiS_Pr->SiS_VBType & VB_SIS301) {
         SetEdgeEnhance(SiS_Pr,ModeNo,ModeIdIndex);
      }
   }
}
