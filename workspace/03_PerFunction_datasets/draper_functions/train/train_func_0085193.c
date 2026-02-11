my_lengthsp_mb2(CHARSET_INFO *cs __attribute__((unused)),
                const char *ptr, size_t length)
{
  const char *end= ptr + length;
  while (end > ptr + 1 && end[-1] == ' ' && end[-2] == '\0')
    end-= 2;
  return (size_t) (end - ptr);
}
