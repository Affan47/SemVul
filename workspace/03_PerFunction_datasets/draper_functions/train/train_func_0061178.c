setchr4r(int r, unsigned int A, unsigned int V)
{
  if(!CHRptr[r]) return;
  FCEUPPU_LineUpdate();
  V&=CHRmask4[r];
  VPageR[(A)>>10]=VPageR[((A)>>10)+1]=
  VPageR[((A)>>10)+2]=VPageR[((A)>>10)+3]=&CHRptr[r][(V)<<12]-(A);
  if(CHRram[r])
   PPUCHRRAM|=(15<<(A>>10));
  else
   PPUCHRRAM&=~(15<<(A>>10));
}
