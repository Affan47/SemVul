datestrwww(double t, int32_t jl, int32_t acr, char* buf) {
  _assert_(acr >= 0 && buf);
  if (kc::chknan(t)) t = kc::time();
  double tinteg, tfract;
  tfract = std::fabs(std::modf(t, &tinteg));
  if (jl == kc::INT32MAX) jl = jetlag();
  if (acr > 12) acr = 12;
  time_t tt = (time_t)tinteg + jl;
  struct std::tm ts;
  if (!getgmtime(tt, &ts)) std::memset(&ts, 0, sizeof(ts));
  ts.tm_year += 1900;
  ts.tm_mon += 1;
  jl /= 60;
  char tzone[16];
  if (jl == 0) {
    std::sprintf(tzone, "Z");
  } else if (jl < 0) {
    jl *= -1;
    std::sprintf(tzone, "-%02d:%02d", jl / 60, jl % 60);
  } else {
    std::sprintf(tzone, "+%02d:%02d", jl / 60, jl % 60);
  }
  if (acr < 1) {
    std::sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d%s",
                 ts.tm_year, ts.tm_mon, ts.tm_mday, ts.tm_hour, ts.tm_min, ts.tm_sec, tzone);
  } else {
    char dec[16];
    std::sprintf(dec, "%.12f", tfract);
    char* wp = dec;
    if (*wp == '0') wp++;
    wp[acr+1] = '\0';
    std::sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d%s%s",
                 ts.tm_year, ts.tm_mon, ts.tm_mday, ts.tm_hour, ts.tm_min, ts.tm_sec, wp, tzone);
  }
}
