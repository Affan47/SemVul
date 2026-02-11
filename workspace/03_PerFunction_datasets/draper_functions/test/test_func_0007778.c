SeparTwoReals(dcmpx Buff[], dcmpx Out0[], dcmpx Out1[])
{ int idx,HalfSize=Size/2;


  Out0[0].re=Buff[0].re; Out1[0].re=Buff[0].im;
  for(idx=1; idx<HalfSize; idx++)
  { Out0[idx].re=  Buff[idx].re +Buff[Size-idx].re;
    Out0[idx].im=  Buff[idx].im -Buff[Size-idx].im;
    Out1[idx].re=  Buff[idx].im +Buff[Size-idx].im;
    Out1[idx].im=(-Buff[idx].re)+Buff[Size-idx].re;
  } Out0[0].im=Buff[HalfSize].re; Out1[0].im=Buff[HalfSize].im;


}
