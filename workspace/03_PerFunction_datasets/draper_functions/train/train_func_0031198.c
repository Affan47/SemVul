ROM_BANK16(uint32 A, uint32 V)
{
 setprg16(A,V);
 if(A>=0x8000)
 {
  PRGBankList[((A-0x8000)>>13)]=V<<1;
  PRGBankList[((A-0x8000)>>13)+1]=(V<<1)+1;
 }
}
