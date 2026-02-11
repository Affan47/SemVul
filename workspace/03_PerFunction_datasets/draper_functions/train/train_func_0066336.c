saa1099_envelope(int chip, int ch)
{
	struct SAA1099 *saa = &saa1099[chip];
	if (saa->env_enable[ch])
	{
		int step, mode, mask;
        mode = saa->env_mode[ch];

		step = saa->env_step[ch] =
			((saa->env_step[ch] + 1) & 0x3f) | (saa->env_step[ch] & 0x20);

		mask = 15;
        if (saa->env_bits[ch])
			mask &= ~1;

        saa->channels[ch*3+0].envelope[ LEFT] =
		saa->channels[ch*3+1].envelope[ LEFT] =
		saa->channels[ch*3+2].envelope[ LEFT] = envelope[mode][step] & mask;
		if (saa->env_reverse_right[ch] & 0x01)
		{
			saa->channels[ch*3+0].envelope[RIGHT] =
			saa->channels[ch*3+1].envelope[RIGHT] =
			saa->channels[ch*3+2].envelope[RIGHT] = (15 - envelope[mode][step]) & mask;
		}
		else
		{
			saa->channels[ch*3+0].envelope[RIGHT] =
			saa->channels[ch*3+1].envelope[RIGHT] =
			saa->channels[ch*3+2].envelope[RIGHT] = envelope[mode][step] & mask;
        }
	}
	else
	{

		saa->channels[ch*3+0].envelope[ LEFT] =
		saa->channels[ch*3+1].envelope[ LEFT] =
		saa->channels[ch*3+2].envelope[ LEFT] =
		saa->channels[ch*3+0].envelope[RIGHT] =
		saa->channels[ch*3+1].envelope[RIGHT] =
		saa->channels[ch*3+2].envelope[RIGHT] = 16;
    }
}
