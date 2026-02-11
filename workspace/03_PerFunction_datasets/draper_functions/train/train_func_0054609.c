operator>(const timespec& tm) {
  return (sec > tm.tv_sec ||
          (sec == tm.tv_sec && msec > (tm.tv_nsec / 1000000)));
}
