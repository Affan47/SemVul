cc_telemetry_cksum(const union ao_telemetry_all *telemetry)
{
	const uint8_t	*x = (const uint8_t *) telemetry;
	int i;
	uint8_t	sum = 0x5a;
	for (i = 0; i < 34; i++)
		sum += x[i];
	return sum;
}
