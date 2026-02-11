half_phase(half_iir_t * p, float * buf, int len)
{
  float const small_normal = 1/MULT32/MULT32;
  int i;
  for (i = 0; i < len; buf[i] = (float)half_iir1(p, buf[i], 0), ++i);
#define _ p->y[i] += small_normal, i += 2;
  i = 0, _ IIR_FILTER
#undef _
#define _ p->y[i] -= small_normal, i += 2;
  i = 0, _ IIR_FILTER
#undef _
}
