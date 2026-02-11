LCompare(char *name, LObject *expr1, LObject *expr2)
{
  char *s1, *s2;
  float e1, e2;
  if (expr1->type == LSTRING && expr2->type == LSTRING) {
    s1 = LSTRINGVAL(expr1);
    s2 = LSTRINGVAL(expr2);
    return -strcmp(s1,s2);
  }
  if (expr1->type == LINT) e1 = LINTVAL(expr1);
  else if (expr1->type == LFLOAT) e1 = LFLOATVAL(expr1);
  else {
    OOGLError(0, "%s: arg 1 must be int, float, or string\n", name);
    return -2;
  }
  if (expr2->type == LINT) e2 = LINTVAL(expr2);
  else if (expr2->type == LFLOAT) e2 = LFLOATVAL(expr2);
  else {
    OOGLError(0, "%s: arg 2 must be int, float, or string\n", name);
    return -2;
  }
  if (e1 == e2) return 0;
  else if (e1 > e2) return 1;
  else return -1;
}
