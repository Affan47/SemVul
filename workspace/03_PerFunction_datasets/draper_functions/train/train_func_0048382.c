mds_mult(const unsigned char *in, unsigned char *out)
{
  int x;
  ulong32 tmp;
  for (tmp = x = 0; x < 4; x++) {
      tmp ^= mds_column_mult(in[x], x);
  }
  STORE32L(tmp, out);
}
