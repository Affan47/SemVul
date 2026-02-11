sh6840_update_noise(int clocks)
{
	UINT8 history = sh6840_noise_history;
	int noise_clocks = 0;
	int i;


	for (i = 0; i < clocks * 2; i++)
	{

		history = (history << 1) | (rand() & 1);


		if ((history & 0x03) == 0x01)
		{
			sh6840_noise_state ^= 1;
			noise_clocks += sh6840_noise_state;
		}
	}


	sh6840_noise_history = history;
	return noise_clocks;
}
