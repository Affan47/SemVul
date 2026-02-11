ymf278_compute_decay_rate(int num)
{
	int samples;

	if (num <= 3)
		samples = 0;
	else if (num >= 60)
		samples = 15 << 4;
	else
	{
		samples = (15 << (21 - num / 4)) / (4 + num % 4);
		if (num % 4 && num / 4 <= 11)
			samples += 2;
		else if (num == 51)
			samples += 2;
	}

	return ((UINT64)samples * Machine->sample_rate) / 44100;
}
