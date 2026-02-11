strndup (const wchar_t *str, size_t n)
{
  const wchar_t *t = str;
  size_t len;


  for (len = 0;
       len < n && *t++ != '\0';
       len++)
    continue;

  wchar_t *s;
  ACE_ALLOCATOR_RETURN (s,
                        static_cast<wchar_t *> (
            ACE_OS::malloc ((len + 1) * sizeof (wchar_t))),
                        0);
  return ACE_OS::strsncpy (s, str, len + 1);
}
