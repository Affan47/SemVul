TEMP_RANGE_TO_REG(long val, int reg)
{
	int i;

	for (i = 15; i > 0; i--) {
		if (val > (TEMP_RANGE[i] + TEMP_RANGE[i - 1] + 1) / 2)
			break;
	}

	return (reg & 0x0f) | (i << 4);
}
