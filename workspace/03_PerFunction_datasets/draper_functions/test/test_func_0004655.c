Hmalloc (size)
  unsigned int size;
{
  unsigned int s = (size + 4) & 0xfffffffc;
  char * p = malloc (s);
  if (p != NULL)
    memset (p, 0, s);
  else
    bail ("Hmalloc %d failed", s);
  return (p);
}
