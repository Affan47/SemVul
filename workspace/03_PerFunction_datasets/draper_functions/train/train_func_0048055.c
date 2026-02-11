dcs_dac_update(int num, INT16 *buffer, int length)
{
	UINT32 current, step, indx;
	INT16 *source;
	int i;


	if (dcs.enabled)
	{
		source = dcs.buffer;
		current = dcs.sample_position;
		step = dcs.sample_step;


		for (i = 0; i < length; i++)
		{
			indx = current >> 16;
			if (indx >= dcs.buffer_in)
				break;
			current += step;
			*buffer++ = source[indx & DCS_BUFFER_MASK];
		}

		if (LOG_BUFFER_FILLING && i < length)
			logerror("DCS ran out of input data\n");


		for ( ; i < length; i++)
			*buffer++ = source[(dcs.buffer_in - 1) & DCS_BUFFER_MASK];


		while (current >= (DCS_BUFFER_SIZE << 16))
		{
			current -= DCS_BUFFER_SIZE << 16;
			dcs.buffer_in -= DCS_BUFFER_SIZE;
		}

		if (LOG_BUFFER_FILLING)
			logerror("DCS dac update: bytes in buffer = %d\n", dcs.buffer_in - (current >> 16));


		dcs.sample_position = current;
	}
	else
		memset(buffer, 0, length * sizeof(INT16));
}
