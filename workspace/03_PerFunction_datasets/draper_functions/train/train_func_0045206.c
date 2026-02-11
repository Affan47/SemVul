comefromsearch(tuple* tn, unsigned int index)
{
  tuple* tp;
  for (tp = tuples; tp < tuples + ick_lineno; tp++)
  {
    if((tp->type == COME_FROM || tp->type == NEXTFROMLABEL)
	&& tp->u.target == (unsigned)(tn-tuples+1))
      index--;
    if(!index) return tp-tuples+1;
  }
  return -1;
}
