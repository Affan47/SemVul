s48_stop_alarm_interrupts(void)
{
  struct itimerval newv, old;

  newv.it_value.tv_sec = 0;
  newv.it_value.tv_usec = 0;
  newv.it_interval.tv_sec = 0;
  newv.it_interval.tv_usec = 0;
  if (0 != setitimer(ITIMER_REAL, &newv, &old)) {
    perror("setitimer");
    exit(-1); }
}
