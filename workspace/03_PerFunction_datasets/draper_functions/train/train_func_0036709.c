timer_create_with_offset(m_tmcnt_t interval,m_tmcnt_t offset,
                                  int level,timer_proc callback,void *user_arg)
{
   timer_entry_t *timer;


   if (!(timer = malloc(sizeof(*timer))))
      return(0);

   timer->interval = interval;
   timer->offset = 0;
   timer->callback = callback;
   timer->user_arg = user_arg;
   timer->flags = 0;
   timer->level = level;
   timer->flags |= TIMER_BOUNDARY;

   return(timer_enable(timer));
}
