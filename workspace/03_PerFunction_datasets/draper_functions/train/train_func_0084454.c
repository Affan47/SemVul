gf_multby_zero(void *dest, int bytes, int xor)
{
  if (xor) return;
  bzero(dest, bytes);
  return;
}
