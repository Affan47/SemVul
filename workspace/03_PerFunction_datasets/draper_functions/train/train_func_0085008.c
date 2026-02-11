sync_time(int ms)
{
	if(labs((int)audio_timer - ms) > 1000)
		audio_timer = (double)ms;
	else
		audio_timer = audio_timer * 0.95 + (double)ms * 0.05;
}
