butTimer_fCreate(void *packet, But *but, struct timeval delay,
			    int frequency, bool winOnly,
			    ButOut (*timerFunc)(ButTimer *timer))  {
  ButTimer  *bt;
  struct timeval  now;
  struct timezone  tzone;
  int  i;

  bt = wms_malloc(sizeof(ButTimer));
  MAGIC_SET(bt);
  bt->packet = packet;
  bt->eventNum = 0;
  bt->period.tv_sec = 0;
  bt->winOnly = winOnly;
  if (frequency < BUTTIMER_MAXFREQ)  {
    bt->period.tv_usec = 1000000 / frequency;
    bt->ticksPerPeriod = 1;
  } else  {
    bt->period.tv_usec = 1000000 / BUTTIMER_STDFREQ;
    bt->ticksPerPeriod = (frequency + BUTTIMER_STDFREQ/2) /
      BUTTIMER_STDFREQ;
  }
  bt->state = butTimer_on;
  gettimeofday(&now, &tzone);
  bt->nextFiring = but_timerAdd(now, delay);
  if (but)
    bt->win = but->win;
  else
    bt->win = NULL;
  bt->but = but;
  bt->timerFunc = timerFunc;
  bt->next = but_timerList;
  bt->freqCounter = TRUE;
  for (i = 0;  i < BUTTIMER_HIST;  ++i)
    bt->lastRes[i] = 1;
  bt->resnum = 0;
  bt->ticksLeft = 0;
  but_timerList = bt;
  return(bt);
}
