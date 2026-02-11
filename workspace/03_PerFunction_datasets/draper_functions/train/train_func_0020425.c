SiS_CheckACK(struct SiS_Private *SiS_Pr)
{
  unsigned short tempah;

  SiS_SetSCLKLow(SiS_Pr);
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  SiS_Pr->SiS_DDC_Data);
  SiS_SetSCLKHigh(SiS_Pr);
  tempah = SiS_GetReg(SiS_Pr->SiS_DDC_Port,SiS_Pr->SiS_DDC_Index);
  SiS_SetSCLKLow(SiS_Pr);
  if(tempah & SiS_Pr->SiS_DDC_Data) return 1;
  return 0;
}
