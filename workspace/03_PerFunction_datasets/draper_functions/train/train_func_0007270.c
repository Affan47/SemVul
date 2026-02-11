SiS_CalcDelay(struct SiS_Private *SiS_Pr, unsigned short VCLK,
		unsigned short colordepth, unsigned short MCLK)
{
   unsigned short temp1, temp2;

   temp2 = SiS_DoCalcDelay(SiS_Pr, MCLK, VCLK, colordepth, 0);
   temp1 = SiS_DoCalcDelay(SiS_Pr, MCLK, VCLK, colordepth, 1);
   if(temp1 < 4) temp1 = 4;
   temp1 -= 4;
   if(temp2 < temp1) temp2 = temp1;
   return temp2;
}
