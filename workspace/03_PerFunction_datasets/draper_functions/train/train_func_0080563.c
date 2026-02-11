BCDToDecimal(UINT32 value)
{
	UINT32	accumulator = 0;
	UINT32	multiplier = 1;
	int		i;

	for(i = 0; i < 8; i++)
	{
		accumulator += (value & 0xF) * multiplier;

		multiplier *= 10;
		value >>= 4;
	}

	return accumulator;
}
