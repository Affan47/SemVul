decimal_result_size(decimal_t *from1, decimal_t *from2, char op, int param)
{
  switch (op) {
  case '-':
    return ROUND_UP(max(from1->intg, from2->intg)) +
           ROUND_UP(max(from1->frac, from2->frac));
  case '+':
    return ROUND_UP(max(from1->intg, from2->intg)+1) +
           ROUND_UP(max(from1->frac, from2->frac));
  case '*':
    return ROUND_UP(from1->intg+from2->intg)+
           ROUND_UP(from1->frac)+ROUND_UP(from2->frac);
  case '/':
    return ROUND_UP(from1->intg+from2->intg+1+from1->frac+from2->frac+param);
  default: DBUG_ASSERT(0);
  }
  return -1;
}
