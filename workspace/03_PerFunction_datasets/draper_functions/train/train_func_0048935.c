run( nes_time_t time, nes_time_t end_time )
{
	const int timer_period = period() + 1;
	if ( !output )
	{
		time += delay;
		delay = 0;
		if ( length_counter && linear_counter && timer_period >= 3 )
			delay = maintain_phase( time, end_time, timer_period ) - end_time;
		return;
	}

	output->set_modified();


	int delta = update_amp( calc_amp() );
	if ( delta )
		synth.offset( time, delta, output );

	time += delay;
	if ( length_counter == 0 || linear_counter == 0 || timer_period < 3 )
	{
		time = end_time;
	}
	else if ( time < end_time )
	{
		Blip_Buffer* const output = this->output;

		int phase = this->phase;
		int volume = 1;
		if ( phase > phase_range ) {
			phase -= phase_range;
			volume = -volume;
		}

		do {
			if ( --phase == 0 ) {
				phase = phase_range;
				volume = -volume;
			}
			else {
				synth.offset_inline( time, volume, output );
			}

			time += timer_period;
		}
		while ( time < end_time );

		if ( volume < 0 )
			phase += phase_range;
		this->phase = phase;
		last_amp = calc_amp();
 	}
	delay = time - end_time;
}
