mod255(int c)
{
  char *cp = (char *) (&c);
  char *end_cp = cp + sizeof(c);
  int r = 0;

  while (cp < end_cp) {
    r += *(unsigned char *) (cp++);
  }
  while (r >= 255)
    r -= 255;

  return r;
}
