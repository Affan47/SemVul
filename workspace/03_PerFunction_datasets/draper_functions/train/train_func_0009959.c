compile(const std::string& regex, uint32_t opts) {
#if _KC_PXREGEX
  _assert_(true);
  RegexCore* core = (RegexCore*)opq_;
  if (core->alive) {
    ::regfree(&core->rbuf);
    core->alive = false;
  }
  int32_t cflags = REG_EXTENDED;
  if (opts & IGNCASE) cflags |= REG_ICASE;
  if ((opts & MATCHONLY) || regex.empty()) {
    cflags |= REG_NOSUB;
    core->nosub = true;
  }
  if (::regcomp(&core->rbuf, regex.c_str(), cflags) != 0) return false;
  core->alive = true;
  return true;
#else
  _assert_(true);
  RegexCore* core = (RegexCore*)opq_;
  if (core->rbuf) {
    delete core->rbuf;
    core->rbuf = NULL;
  }
  int32_t cflags = std::regex::ECMAScript;
  if (opts & IGNCASE) cflags |= std::regex::icase;
  if ((opts & MATCHONLY) || regex.empty()) cflags |= std::regex::nosubs;
  try {
    core->rbuf = new std::regex(regex, (std::regex::flag_type)cflags);
  } catch (...) {
    core->rbuf = NULL;
    return false;
  }
  return true;
#endif
}
