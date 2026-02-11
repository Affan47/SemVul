GetOEMTVPtr(struct SiS_Private *SiS_Pr)
{
  unsigned short index;

  index = 0;
  if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))  index += 4;
  if(SiS_Pr->SiS_VBType & VB_SISVB) {
     if(SiS_Pr->SiS_VBInfo & SetCRT2ToSCART)  index += 2;
     else if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) index += 3;
     else if(SiS_Pr->SiS_TVMode & TVSetPAL)   index += 1;
  } else {
     if(SiS_Pr->SiS_TVMode & TVSetCHOverScan) index += 2;
     if(SiS_Pr->SiS_TVMode & TVSetPAL)        index += 1;
  }
  return index;
}
