subbandsynthesis(REAL *fractionL,REAL *fractionR)
{
  if(downfrequency)
  {
    subbandsynthesis_2(fractionL,fractionR);
    return;
  }

  computebuffer(fractionL,calcbufferL);
  if(!outputstereo)generatesingle();
  else
  {
    computebuffer(fractionR,calcbufferR);
    generate();
  }

  if(calcbufferoffset<15)calcbufferoffset++;
  else calcbufferoffset=0;

  currentcalcbuffer^=1;
}
