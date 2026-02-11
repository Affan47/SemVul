_workarounds_strcat (char *strbuf,
                     unsigned int bitmask,
                     unsigned int mask,
                     const char *str,
                     int *is_first)
{
  assert (strbuf && str && is_first);

  if (bitmask & mask)
    {
      if ((*is_first))
        strcat (strbuf, ",");
      strcat (strbuf, str);
      (*is_first)++;
    }
}
