input_callback(int dummy)
{
	static UINT8 dial[4];


	int i;

	for (i = 0; i < 4; i++)
	{
		signed char delta = readinputport(5 + i) - dial[i];

		if (delta < 0)
		{
			steer_dir[i] = 0;
		}
		if (delta > 0)
		{
			steer_dir[i] = 1;
		}

		steer_flag[i] = dial[i] & 1;

		switch (readinputport(9 + i))
		{
		case 1: gear[i] = 1; break;
		case 2: gear[i] = 2; break;
		case 4: gear[i] = 3; break;
		case 8: gear[i] = 4; break;
		}

		dial[i] += delta;
	}
}
