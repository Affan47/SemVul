memmatch(const char *haystack, size_t haystack_len,
                            const char *needle, size_t needle_len) {
  if (needle_len == 0)
    return haystack;
  else if (needle_len > haystack_len)
    return NULL;

  const char* match;
  const char* hayend = haystack + haystack_len - needle_len + 1;
  while ((match = (const char*)memchr(haystack, needle[0],
                                      hayend - haystack))) {
    if (memcmp(match, needle, needle_len) == 0)
      return match;
    else
      haystack = match + 1;
  }
  return NULL;
}
