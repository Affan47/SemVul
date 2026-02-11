getaname(A aname)
{
  C *name;
  if (Ct==aname->t) name=(C *)aname->p;
  else if (Et==aname->t && QS(aname->p[0])) name=XS(aname->p[0])->n;
  else name=(C *)0;
  R name;
}
