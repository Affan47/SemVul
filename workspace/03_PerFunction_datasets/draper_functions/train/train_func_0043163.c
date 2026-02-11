uv__strlcpy(char* dst, const char* src, size_t size) {
  const char *org;

  if (size == 0) {
    return 0;
  }

  org = src;
  while (--size && *src) {
    *dst++ = *src++;
  }
  *dst = '\0';

  return src - org;
}
