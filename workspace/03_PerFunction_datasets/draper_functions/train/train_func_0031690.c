vprintf(const char * format, va_list ap0)
  {
    reserve(size() + 64);
    int res = 0;
    va_list ap;
  loop: {
      int avail = storage_end_ - end_;
      if (res < 0 && avail > 1024*1024)
        return -1;


      va_copy(ap,ap0);
      res = vsnprintf(end_, avail, format, ap);
      va_end(ap);
      if (res < 0) {
        reserve_i(); goto loop;
      } else if (res > avail) {
        reserve_i(size() + res); goto loop;
      }
    }
    end_ += res;
    return res;
  }
