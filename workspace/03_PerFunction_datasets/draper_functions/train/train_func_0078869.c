replace(const std::string& str, const std::string& alt) {
#if _KC_PXREGEX
  _assert_(true);
  RegexCore* core = (RegexCore*)opq_;
  if (!core->alive || core->nosub) return str;
  regmatch_t subs[256];
  if (::regexec(&core->rbuf, str.c_str(), sizeof(subs) / sizeof(*subs), subs, 0) != 0)
    return str;
  const char* sp = str.c_str();
  std::string xstr;
  bool first = true;
  while (sp[0] != '\0' && ::regexec(&core->rbuf, sp, 10, subs, first ? 0 : REG_NOTBOL) == 0) {
    first = false;
    if (subs[0].rm_so == -1) break;
    xstr.append(sp, subs[0].rm_so);
    for (const char* rp = alt.c_str(); *rp != '\0'; rp++) {
      if (*rp == '$') {
        if (rp[1] >= '0' && rp[1] <= '9') {
          int32_t num = rp[1] - '0';
          if (subs[num].rm_so != -1 && subs[num].rm_eo != -1)
            xstr.append(sp + subs[num].rm_so, subs[num].rm_eo - subs[num].rm_so);
          ++rp;
        } else if (rp[1] == '&') {
          xstr.append(sp + subs[0].rm_so, subs[0].rm_eo - subs[0].rm_so);
          ++rp;
        } else if (rp[1] != '\0') {
          xstr.append(++rp, 1);
        }
      } else {
        xstr.append(rp, 1);
      }
    }
    sp += subs[0].rm_eo;
    if (subs[0].rm_eo < 1) break;
  }
  xstr.append(sp);
  return xstr;
#else
  _assert_(true);
  RegexCore* core = (RegexCore*)opq_;
  if (!core->rbuf) return str;
  return std::regex_replace(str, *core->rbuf, alt);
#endif
}


}
