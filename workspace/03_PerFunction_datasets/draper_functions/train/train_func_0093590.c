slogic_parse_sample_rate(const char *str)
{
	struct slogic_sample_rate *sample_rate = slogic_get_sample_rates();
	while (sample_rate->text != NULL) {
		if (strcmp(sample_rate->text, str) == 0) {
			return sample_rate;
		}
		sample_rate++;
	}
	return NULL;
}
