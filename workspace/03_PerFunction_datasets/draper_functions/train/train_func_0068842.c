goTime_endTimer(const GoTime *time, GoTimer *timer)  {
  bool  result;
  int  left;

  result = goTime_checkTimer(time, timer);
  if (time->type == goTime_japanese)  {
    left = timer->timeLeft;
    if (timer->usLeft)
      ++left;
    if ((left > 0) && (left <= time->aux * time->by))  {
      left = (left + time->by - 1);
      timer->timeLeft = left - (left % time->by);
      timer->usLeft = 0;
    }
  } else if (time->type == goTime_canadian)  {
    if (timer->aux)  {
      --timer->aux;
      if (timer->aux == 0)  {
	timer->aux = time->aux;
	timer->timeLeft = time->by;
	timer->usLeft = 0;
      }
    }
  }
  return(result);
}
