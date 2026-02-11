skipblank (const char *s)
{
  initatom ();
  while (is_space (*s))
    s++;
  return s;
}
