reload_count(int counter)
{
	double period;
	int count;


	m6840_state[counter].count = m6840_state[counter].latch;


	if (counter == 0 && !(m6840_state[counter].control & 0x02))
	{
		timer_adjust(m6840_state[counter].timer, TIME_NEVER, 0, 0);
		m6840_state[counter].timer_active = 0;
		return;
	}


	if (m6840_state[counter].control & 0x02)
		period = m6840_internal_counter_period;
	else
		period = m6840_counter_periods[counter];


	count = m6840_state[counter].count;
	if (m6840_state[counter].control & 0x04)
		count = ((count >> 8) + 1) * ((count & 0xff) + 1);
	else
		count = count + 1;


	timer_adjust(m6840_state[counter].timer, period * (double)count, (count << 2) + counter, 0);
	m6840_state[counter].timer_active = 1;
}
