coq_pushpop (value i) {
  code_t res;
  int n;
  n = Int_val(i);
  if (n == 0) {
    res = coq_stat_alloc(4);
    *res = VALINSTR(STOP);
    return (value)res;
  }
  else {
    code_t q;
    res = coq_stat_alloc(12);
    q = res;
    *q++ = VALINSTR(POP);
    *q++ = (opcode_t)n;
    *q = VALINSTR(STOP);
    return (value)res;
  }
}
