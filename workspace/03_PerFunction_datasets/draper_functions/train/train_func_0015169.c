timer_update(struct _memory_segment *s)
{


	struct _timer_data *timer = (struct _timer_data *)s->data;
	extern struct _board_data board_data;


	if(!timer->enable) return;

	if(board_data.use_timer_hack) {


	} else {


		if(board_data.cycle_count < timer->next_tick)
			goto check_interrupts;
		timer->next_tick += timer->cycles_per_tick;
	}


	if(timer->TCN == timer->TRR) {

		TRACE("         %s: TCN == TRR = %ld\n", s->name, timer->TRR);
		timer->TER.REF=1;
		if(timer->TMR.FRR) {
			TRACE("         %s: Restart flag is on, restarting the timer\n", s->name);

			timer->TCN=0;
		}
	} else {

		timer->TER.REF=0;
	}


	timer->TCN++;

check_interrupts:


	if(timer->TER.REF && timer->TMR.ORI) {
		TRACE("          %s: timer reference condition exists\n", s->name);
		goto interrupts_on;
	}


	sim->interrupt_withdraw(s->interrupt_line);
	return;

interrupts_on:
	TRACE("          Posting interrupt request for %s\n", s->name);
	sim->interrupt_assert(s->interrupt_line, 0);
	return;


}
