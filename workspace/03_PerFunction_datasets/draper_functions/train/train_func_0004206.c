determine_spacelen(char *s)
{
  int spacelen = 0;
  while (*s == ' ') { spacelen++; s++; }
  return spacelen;
}
