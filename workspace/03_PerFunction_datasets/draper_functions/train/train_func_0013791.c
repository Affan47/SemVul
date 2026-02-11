Cudd_ReadIthClause(
  DdTlcInfo * tlc,
  int i,
  DdHalfWord *var1,
  DdHalfWord *var2,
  int *phase1,
  int *phase2)
{
    if (tlc == NULL) return(0);
    if (tlc->vars == NULL || tlc->phases == NULL) return(0);
    if (i < 0 || (unsigned) i >= tlc->cnt) return(0);
    *var1 = tlc->vars[2*i];
    *var2 = tlc->vars[2*i+1];
    *phase1 = (int) bitVectorRead(tlc->phases, 2*i);
    *phase2 = (int) bitVectorRead(tlc->phases, 2*i+1);
    return(1);

}
