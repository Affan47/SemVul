qes_get_rate_size(u32 idx, const unsigned int *rates, const unsigned int nb_rates)
{
	u32 i;
	for (i=0; i<nb_rates; i++) {
		if (rates[2*i]==idx) return rates[2*i+1];
	}
	return 0;
}
