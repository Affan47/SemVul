isEqual(ELObj &obj)
{
  PairObj *p = obj.asPair();

  return p && equal(*p->car(), *car()) && equal(*p->cdr(), *cdr());
}
