Sleep(SleepInterval full_or_half) {


    useconds_t interval = sampler_->interval_ * 1000 - 100;
    if (full_or_half == HALF_INTERVAL) interval /= 2;
    int result = usleep(interval);
#ifdef DEBUG
    if (result != 0 && errno != EINTR) {
      fprintf(stderr,
              "SignalSender usleep error; interval = %u, errno = %d\n",
              interval,
              errno);
      ASSERT(result == 0 || errno == EINTR);
    }
#endif
    USE(result);
  }
