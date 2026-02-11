strnchr (const ACE_WCHAR_T *s, ACE_WCHAR_T c, size_t len)
{
  for (size_t i = 0; i < len; ++i)
    {
      if (s[i] == c)
        {
          return s + i;
        }
    }

  return 0;
}
