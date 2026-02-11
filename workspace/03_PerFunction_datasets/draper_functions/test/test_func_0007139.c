reset()
{
	last_time = 0;

	for ( int i = 0; i < osc_count; i++ )
		oscs [i].last_amp = 0;

	fme7_apu_state_t* state = this;
	memset( state, 0, sizeof *state );
}
