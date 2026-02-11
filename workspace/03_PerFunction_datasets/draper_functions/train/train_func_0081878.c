timers_loaded()
{
	int i;
	for ( i = 0; i < timer_count; i++ )
	{
		Timer* t = &m.timers [i];
		t->period  = IF_0_THEN_256( REGS [r_t0target + i] );
		t->enabled = REGS [r_control] >> i & 1;
		t->counter = REGS_IN [r_t0out + i] & 0x0F;
	}

	set_tempo( m.tempo );
}
