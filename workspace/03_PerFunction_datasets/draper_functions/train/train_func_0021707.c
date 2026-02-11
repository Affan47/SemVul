maintain_phase( nes_time_t time, nes_time_t end_time,
		nes_time_t timer_period )
{
	nes_time_t remain = end_time - time;
	if ( remain > 0 )
	{
		int count = (remain + timer_period - 1) / timer_period;
		phase = (phase + count) & (phase_range - 1);
		time += (blargg_long) count * timer_period;
	}
	return time;
}
