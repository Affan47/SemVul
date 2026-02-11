def_tmr_event(int dev, unsigned char *event)
{
	unsigned char   cmd = event[1];
	unsigned long   parm = *(int *) &event[4];

	switch (cmd)
	  {
	  case TMR_WAIT_REL:
		  parm += prev_event_time;
	  case TMR_WAIT_ABS:
		  if (parm > 0)
		    {
			    long            time;

			    if (parm <= curr_ticks)
				    return TIMER_NOT_ARMED;

			    time = parm;
			    next_event_time = prev_event_time = time;

			    return TIMER_ARMED;
		    }
		  break;

	  case TMR_START:
		  tmr_reset();
		  tmr_running = 1;
		  break;

	  case TMR_STOP:
		  tmr_running = 0;
		  break;

	  case TMR_CONTINUE:
		  tmr_running = 1;
		  break;

	  case TMR_TEMPO:
		  if (parm)
		    {
			    if (parm < 8)
				    parm = 8;
			    if (parm > 360)
				    parm = 360;
			    tmr_offs = tmr_ctr;
			    ticks_offs += tmr2ticks(tmr_ctr);
			    tmr_ctr = 0;
			    curr_tempo = parm;
		    }
		  break;

	  case TMR_ECHO:
		  seq_copy_to_input(event, 8);
		  break;

	  default:;
	  }

	return TIMER_NOT_ARMED;
}
