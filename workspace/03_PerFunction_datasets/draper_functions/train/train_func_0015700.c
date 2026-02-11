SyroFunc_GetSinValue(int phase, bool bData)
{
	int32_t ret;

	ret = sin_table[phase];

	if (bData) {
		if (ret > 0) {
			ret = 32767 - ret;
			ret = ((ret * ret) / 32767);
			ret = 32767 - ret;
		} else if (ret < 0) {
			ret += 32767;
			ret = ((ret * ret) / 32767);
			ret -= 32767;
		}
	}

	return (int16_t)ret;
}
