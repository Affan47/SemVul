PLATFORM_AdjustSpeed(void)
{
	int bytes_per_sample = (POKEYSND_stereo_enabled ? 2 : 1)*((sound_bits == 16) ? 2:1);

	double alpha = 2.0/(1.0+40.0);
	int gap_too_small;
	int gap_too_large;
	static int inited = FALSE;

	if (!inited) {
		inited = TRUE;
		avg_gap = gap_est;
	}
	else {
		avg_gap = avg_gap + alpha * (gap_est - avg_gap);
	}

	gap_too_small = (snddelay*dsprate*bytes_per_sample)/1000;
	gap_too_large = ((snddelay+sndspread)*dsprate*bytes_per_sample)/1000;
	if (avg_gap < gap_too_small) {
		double speed = 0.95;
		return speed;
	}
	if (avg_gap > gap_too_large) {
		double speed = 1.05;
		return speed;
	}
	return 1.0;
}
