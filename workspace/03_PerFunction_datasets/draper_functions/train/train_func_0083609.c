Listen(int limit, bool& error) {
    error = false;
    int h = instance_.Listen();
    if(h == -1) return !(error = true);
    time_t out = (time_t)(-1);
    if(limit >= 0) out = ::time(NULL) + limit;
    int to = 0;
    for(;;) {
      pollfd fd;
      fd.fd = h; fd.events = POLLIN; fd.revents = 0;
      int err = ::poll(&fd, 1, to);

      if((err < 0) && (errno != EINTR)) break;
      if(err > 0) {
        if(err != 1) break;
        if(!(fd.revents & POLLIN)) break;
      };
      time_t now = ::time(NULL);
      time_t next = (time_t)(-1);
      if(err == 1) {

        char c;
        ::read(fd.fd,&c,1);
        last = now; next = now + WATCHDOG_TEST_INTERVAL;
      } else {

        if(last != (time_t)(-1)) next = last + WATCHDOG_TEST_INTERVAL;
        if((next != (time_t)(-1)) && (((int)(next-now)) <= 0)) return true;
      }

      if((limit >= 0) && (((int)(out-now)) <= 0)) return false;

      to = WATCHDOG_TEST_INTERVAL;
      if(next != (time_t)(-1)) {
        int tto = next-now;
        if(tto < to) to = tto;
      }
      if(limit >= 0) {
        int tto = out-now;
        if(tto < to) to = tto;
      }
      if(to < 0) to = 0;
    }

    error = true;
    return false;
  }
