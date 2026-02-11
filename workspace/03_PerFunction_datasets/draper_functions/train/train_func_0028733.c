leland_dac_update(int dacnum, UINT8 sample)
{
	UINT8 *buffer = dac_buffer[dacnum];
	int bufin = dac_bufin[dacnum];


	if (!buffer)
		return;


	buffer[bufin] = sample;
	bufin = (bufin + 1) & DAC_BUFFER_MASK;


	dac_bufin[dacnum] = bufin;
}
