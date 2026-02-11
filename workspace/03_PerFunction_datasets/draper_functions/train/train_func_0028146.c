StrToInt64(const string &s, const string &src, size_t nline,
                 bool allow_negative, bool *error) {
  int64 n;
  const char *cs = s.c_str();
  char *p;
  if (error) *error = false;
  n = strtoll(cs, &p, 10);
  if (p < cs + s.size() || (!allow_negative && n < 0)) {
    FSTERROR() << "StrToInt64: Bad integer = " << s
               << "\", source = " << src << ", line = " << nline;
    if (error) *error = true;
    return 0;
  }
  return n;
}
