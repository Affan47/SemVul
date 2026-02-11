sci_scbrr_calc(struct sci_port *s, unsigned int bps,
				   unsigned long freq)
{
	if (s->sampling_rate)
		return DIV_ROUND_CLOSEST(freq, s->sampling_rate * bps) - 1;


	WARN_ON(1);

	return ((freq + 16 * bps) / (32 * bps) - 1);
}
