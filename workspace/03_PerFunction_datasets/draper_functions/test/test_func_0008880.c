add_one_call(sum_calls *s1, one_call *s2, double units)
{
  if (s2->dir == DIALIN)
  {
    s1->in++;
    s1->din += s2->duration > 0?s2->duration:0;
  }
  else
  {
    s1->out++;
    s1->dout   += s2->duration > 0?s2->duration:0;
    s1->eh     += s2->eh;
    s1->pay    += s2->pay;
  }

  s1->ibytes += s2->ibytes;
  s1->obytes += s2->obytes;
  return 0;
}
