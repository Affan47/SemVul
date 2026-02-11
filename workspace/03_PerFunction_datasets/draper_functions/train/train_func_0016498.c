gln_strncasecmp (const char *s1, const char *s2, size_t n)
{
  size_t index;

  for (index = 0; index < n; index++)
    {
      int diff;

      diff = glk_char_to_lower (s1[index]) - glk_char_to_lower (s2[index]);
      if (diff < 0 || diff > 0)
        return diff < 0 ? -1 : 1;
    }

  return 0;
}
