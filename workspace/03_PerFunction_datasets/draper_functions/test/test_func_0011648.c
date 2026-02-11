SocketSetTimeOut(unsigned long abs_sec, unsigned long abs_nsec,
		 struct timeval& t)
{
  if (abs_sec == 0 && abs_nsec == 0) {

    t.tv_sec = t.tv_usec = 0;
    return;
  }

  unsigned long now_sec, now_nsec;
  omni_thread::get_time(&now_sec,&now_nsec);

  if ((abs_sec <= now_sec) && ((abs_sec < now_sec) || (abs_nsec < now_nsec))) {
    t.tv_sec = t.tv_usec = 0;
  }
  else {
    t.tv_sec = abs_sec - now_sec;
    if (abs_nsec >= now_nsec) {
      t.tv_usec = (abs_nsec - now_nsec) / 1000;
    }
    else {
      t.tv_usec = (1000000000 + abs_nsec - now_nsec) / 1000;
      t.tv_sec -= 1;
    }
  }
}
