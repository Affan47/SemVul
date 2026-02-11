butTimer_create(void *packet, But *but, struct timeval delay,
			   struct timeval period, bool winOnly,
			   ButOut (*timerFunc)(ButTimer *timer))  {
  ButTimer  *bt;
  struct timeval  now;
  struct timezone  tzone;

  bt = wms_malloc(sizeof(ButTimer));
  MAGIC_SET(bt);
  bt->packet = packet;
  bt->eventNum = 0;
  bt->period = period;
  bt->state = butTimer_on;
  gettimeofday(&now, &tzone);
  bt->nextFiring = but_timerAdd(now, delay);
  if (but)
    bt->win = but->win;
  else
    bt->win = NULL;
  bt->but = but;
  bt->timerFunc = timerFunc;
  bt->winOnly = winOnly;
  bt->next = but_timerList;
  bt->freqCounter = FALSE;
  but_timerList = bt;
  return(bt);
}
