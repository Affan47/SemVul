read_ushort(FILE *f, unsigned short *x)
{
  unsigned char s[2];

  if (fread(s, 1, 2, f) != 2) return false;
  *x = (s[1] << 8) + s[0];
  return true;
}
