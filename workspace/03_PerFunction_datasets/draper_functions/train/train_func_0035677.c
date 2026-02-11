linear_reset(void *obj)
{
	struct rate_linear *rate = obj;


	if (rate->old_sample)
		memset(rate->old_sample, 0, sizeof(*rate->old_sample) * rate->channels);
}
