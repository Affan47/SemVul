SiS_Chrontel701xBLOff(struct SiS_Private *SiS_Pr)
{
   unsigned short temp;


   if(SiS_Pr->SiS_IF_DEF_CH70xx == 2) {
      temp = SiS_GetCH701x(SiS_Pr,0x66);
      temp &= 0xDF;
      SiS_SetCH701x(SiS_Pr,0x66,temp);
   }
}
