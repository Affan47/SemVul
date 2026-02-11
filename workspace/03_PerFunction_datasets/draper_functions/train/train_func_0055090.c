YMF262_sh_start(const struct MachineSound *msound)
{
	int i,chip;
	int rate = Machine->sample_rate;

	intf_262 = msound->sound_interface;
	if( intf_262->num > MAX_262 ) return 1;

	if (options.use_filter)
		rate = intf_262->baseclock/288;


	memset(Timer_262,0,sizeof(Timer_262));


	if ( YMF262Init(intf_262->num,intf_262->baseclock,rate) != 0)
		return 1;

	for (chip = 0;chip < intf_262->num; chip++)
	{
		int mixed_vol;
		int vol[4];
		char buf[4][40];
		const char *name[4];

		mixed_vol = intf_262->mixing_levelAB[chip];
		for (i=0; i<4; i++)
		{
			if (i==2)
				mixed_vol = intf_262->mixing_levelCD[chip];
			vol[i] = mixed_vol & 0xffff;
			mixed_vol >>= 16;
			name[i] = buf[i];
			sprintf(buf[i],"%s #%d ch%c",sound_name(msound),chip,'A'+i);
			logerror("%s #%d ch%c",sound_name(msound),chip,'A'+i);
		}
		stream_262[chip] = stream_init_multi(4,name,vol,rate,chip,YMF262UpdateOne);


		YMF262SetTimerHandler (chip, TimerHandler_262, chip*2);
		YMF262SetIRQHandler   (chip, IRQHandler_262, chip);
		YMF262SetUpdateHandler(chip, stream_update, stream_262[chip]);

		Timer_262[chip*2+0] = timer_alloc(timer_callback_262);
		Timer_262[chip*2+1] = timer_alloc(timer_callback_262);
	}
	return 0;
}
