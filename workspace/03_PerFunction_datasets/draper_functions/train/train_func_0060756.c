string_to_ulint(lint &result, const char *p)
{
  result = 0;
  while (*p != '\0') {
    if (*p == '_') { p++; continue; }


    if (*p < '0' || *p > '9') return p;

    lint result2 = (result << 3) + (result << 1) + (*p - '0');


    if (result2 < result) return NULL;
    result = result2;
    p++;
  }

  return p;
}
