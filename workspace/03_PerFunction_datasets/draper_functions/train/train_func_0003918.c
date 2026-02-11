load_state( vrc6_apu_state_t const& in )
{
	reset();
	oscs [2].amp = in.saw_amp;
	for ( int i = 0; i < osc_count; i++ )
	{
		Vrc6_Osc& osc = oscs [i];
		for ( int r = 0; r < reg_count; r++ )
			osc.regs [r] = in.regs [i] [r];

		osc.delay = in.delays [i];
		osc.phase = in.phases [i];
	}
	if ( !oscs [2].phase )
		oscs [2].phase = 1;
}
