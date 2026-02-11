parseString(const char *&token) {
  std::string s;
  token += strspn(token, " \t");
  int e = strcspn(token, " \t\r");
  s = std::string(token, &token[e]);
  token += e;
  return s;
}
