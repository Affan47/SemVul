setToString(const set<Str> & s) {
  Str ret = "";

  if (s.size()>0) {
    ret += "[";
    set<Str>::const_iterator i = s.begin(),
                                  e = s.end();
    CASSERT(i!=e);
    ret += *i;
    ++i;
    for (; i!=e; ++i)
      ret += "," + *i;
    ret += "]";
  }

  return ret;
}
