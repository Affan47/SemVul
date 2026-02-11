fillLed(uint16_t *buffer, uint8_t *color)
{
    int i;

    for(i=0; i<8; i++)
	{
	    buffer[i] = ((color[1]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
	}
	for(i=0; i<8; i++)
	{
	    buffer[8+i] = ((color[0]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
	}
	for(i=0; i<8; i++)
	{
	    buffer[16+i] = ((color[2]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
	}
}
