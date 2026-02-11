MSM5205_playmode_w(int num,int select)
{
	struct MSM5205Voice *voice = &msm5205[num];
	static int prescaler_table[4] = {96,48,64,0};
	int prescaler = prescaler_table[select & 3];
	int bitwidth = (select & 4) ? 4 : 3;


	if( voice->prescaler != prescaler )
	{
		stream_update(voice->stream,0);

		voice->prescaler = prescaler;

		if( prescaler )
		{
			double period = TIME_IN_HZ(msm5205_intf->baseclock / prescaler);
			timer_adjust(voice->timer, period, num, period);
		}
		else
			timer_adjust(voice->timer, TIME_NEVER, 0, 0);
	}

	if( voice->bitwidth != bitwidth )
	{
		stream_update(voice->stream,0);

		voice->bitwidth = bitwidth;
	}
}
