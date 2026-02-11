scan(const char *buf) {
    computed = false;
    int l;
    if (strncasecmp("cksum:", buf, 6) == 0) {
      unsigned long long rr;
      l = sscanf(buf + 6, "%llx", &rr);
      r = rr;
    }
    else {
      int i;
      l = 0;
      for (i = 0; buf[i]; i++)
        if (!isdigit(buf[i]))
          break;
      if (!(buf[i]))
        l = sscanf(buf, "%u", &r);
      else {
        for (i = 0; buf[i]; i++)
          if (!isxdigit(buf[i]))
            break;
        if (!(buf[i])) {
          unsigned long long rr;
          l = sscanf(buf, "%llx", &rr);
          r = rr;
        }
      }
    }
    if (l != 1)
      return;
    computed = true;
    return;
  }
