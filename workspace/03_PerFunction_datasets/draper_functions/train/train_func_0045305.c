d_fetchstr(const unsigned char **ptr, char *dest, unsigned size)
{
  unsigned len;

  len = d_getub(*ptr);

  if (len > 0 && len < size)
    memcpy(dest, *ptr + 1, len);
  else
    len = 0;

  dest[len] = 0;

  *ptr += size;
}
