ctostr(char* des, int len, const std::string& term)
{
  skipbl();
  int ii;
  for (ii = 0;  ii < len && !is_term(term);  ++ii) {
    des[ii] = ctoc();
  }
  des[ii] = '\0';

  while (!is_term(term)) {untested();
    skip();
  }
  skipcom();
}
