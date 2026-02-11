case_starts(const char* a, const char* b) {
  register const char* s=a;
  register const char* t=b;
  for (;;) {
    register unsigned char x,y;
    if (!*t) return 1;
    x = *s - 'A';
    if (x <= 'Z' - 'A') x += 'a'; else x += 'A';
    y = *t - 'A';
    if (y <= 'Z' - 'A') y += 'a'; else y += 'A';
    if (x != y) break;
    if (!x) break;
    ++s; ++t;
  }
  return 0;
}
