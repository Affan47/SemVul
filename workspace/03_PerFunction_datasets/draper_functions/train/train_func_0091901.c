initTimers()
{
  if(timers_array==0) {  timers_array = (struct TimerArrItem * ) malloc(sizeof(struct TimerArrItem)*(TOTAL_TIMERS)); }
  if(timers_array==0)
  {
     fprintf(stderr,"Could not initialize timers , timing operations will fail..\n");
     return ;
  }

  memset(timers_array,0,sizeof(struct TimerArrItem)*(TOTAL_TIMERS) );
}
