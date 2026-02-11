z_ucs_chr(z_ucs *s1, z_ucs chr)
{
  while (*s1 != 0)
  {
    if (*s1 == chr)
      return s1;

    s1++;
  }

  return NULL;
}
