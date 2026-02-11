getString(A aobj)
{
  C *z;
  if (Ct==aobj->t)z=(C *)aobj->p;
  else if (Et==aobj->t&&1==aobj->n&&QS(*aobj->p))z=XS(*aobj->p)->n;
  else z=(C *)0;
  return z;
}
