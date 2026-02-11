butEnv_checkTimers(ButEnv *env, struct timeval *timeout)  {
  struct timeval  current_time, next_timer, timerem;
  struct timezone  tzone;
  bool  take_timer, timer_set = FALSE;
  ButTimer  *bt, *bt2;
  int  ticks, i, orig_ticks;
  int  result = 0;


  for (bt = but_timerList;  bt != NULL;)  {
    if (bt->state == butTimer_dead)  {
      if (bt == but_timerList)
	but_timerList = bt->next;
      else  {
	for (bt2 = but_timerList;  bt2->next != bt;  bt2 = bt2->next);
	bt2->next = bt->next;
      }
      bt2 = bt->next;
      MAGIC_UNSET(bt);
      wms_free(bt);
      bt = bt2;
    } else  {
      bt = bt->next;
    }
  }
  gettimeofday(&current_time, &tzone);
  for (bt = but_timerList;  bt != NULL;  bt = bt->next)  {
    if (bt->state == butTimer_on)  {
      if (timercmp(&bt->nextFiring, &current_time, <))  {
	take_timer = TRUE;
	ticks = but_timerDiv(but_timerSub(current_time, bt->nextFiring),
			     bt->period, &timerem) + 1 + bt->ticksLeft;
	take_timer = TRUE;
	orig_ticks = ticks;
	if (bt->freqCounter)  {
	  for (i = 0;  i < BUTTIMER_HIST;  ++i)  {
	    if (bt->lastRes[i] > ticks)  {
	      take_timer = FALSE;
	    }
	  }
	  if (!bt->ticksLeft)  {
	    bt->lastRes[bt->resnum] = ticks;
	    bt->resnum = (bt->resnum + 1) & (BUTTIMER_HIST - 1);
	  }
	  ticks *= bt->ticksPerPeriod;
	}
	bt->nextFiring = but_timerSub(but_timerAdd(current_time, bt->period),
				       timerem);
	if (take_timer)  {
	  bt->eventNum += ticks;
	  result |= bt->timerFunc(bt);
	  XSync(env->dpy, False);
	  bt->ticksLeft = 0;
	} else
	  bt->ticksLeft += orig_ticks;
      }
      if (!timer_set || timercmp(&bt->nextFiring, &next_timer, <))  {
	timer_set = TRUE;
	next_timer = bt->nextFiring;
      }
    }
  }
  if (timer_set)
    *timeout = but_timerSub(next_timer, current_time);
  else  {
    timeout->tv_usec = 0;
    timeout->tv_sec = 365*24*60*60;
  }
  return(result);
}
