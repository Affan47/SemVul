operator()(char *buffer, size_t buflen)
    {
      while (buflen > 0) {
        int wr = write(1, buffer, buflen);
        if (wr <= 0) {
          if (errno == EINTR || errno == EAGAIN) continue;
          return false;
        }
        buffer += wr;
        buflen -= wr;
      }
      return true;
    }
