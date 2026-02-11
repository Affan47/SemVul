max98925_rate_value(struct snd_soc_codec *codec,
		int rate, int clock, int *value, int *n, int *m)
{
	int ret = -EINVAL;
	int i;

	for (i = 0; i < ARRAY_SIZE(rate_table); i++) {
		if (rate_table[i].rate >= rate) {
			*value = rate_table[i].sr;
			*n = rate_table[i].divisors[clock][0];
			*m = rate_table[i].divisors[clock][1];
			ret = 0;
			break;
		}
	}
	return ret;
}
