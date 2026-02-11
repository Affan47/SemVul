xpow(JML_INT32 x, JML_INT32 y) {
  for (JML_INT32 i = 0; i < y; i++)
    x *= y;
  return x;
}
