expr_to_keyword(const string& input) const
{
  map<string,string>::const_iterator p = object_expr_map.begin();
  regex_t preg;
  string result;
  while(p != object_expr_map.end()) {
    int cflags = REG_EXTENDED | REG_NOSUB;

    if (case_sensitive_expressions() != true)
      cflags |= REG_ICASE;

    regcomp(&preg, p->second.c_str(), cflags);
    if (regexec(&preg, input.c_str(), 0, 0, 0) == 0) {
      ECA_LOG_MSG(ECA_LOGGER::functions, "match (1): " + input + " to regexp " + p->second);
      result = p->first;
      regfree(&preg);
      break;
    }
    regfree(&preg);
    ++p;
  }
  return result;
}
