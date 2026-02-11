gpssat_add(struct cc_gpsdata *data, struct cc_gpssat *sat)
{
	int	i, j;
	int	reuse = 0;
	int	newsizesats;
	struct cc_gpssats	*newsats;

	for (i = data->numsats; --i >= 0;) {
		if (data->sats[i].sat[0].time == sat->time) {
			reuse = 1;
			break;
		}
		if (data->sats[i].sat[0].time < sat->time)
			break;
	}
	if (!reuse) {
		if (data->numsats == data->sizesats) {
			if (data->sizesats == 0)
				newsats = malloc((newsizesats = 256) * sizeof (struct cc_gpssats));
			else
				newsats = realloc (data->sats, (newsizesats = data->sizesats * 2)
						   * sizeof (struct cc_gpssats));
			if (!newsats)
				return 0;
			data->sats = newsats;
			data->sizesats = newsizesats;
		}
		i = data->numsats++;
		data->sats[i].nsat = 0;
	}
	j = data->sats[i].nsat;
	if (j < 12) {
		data->sats[i].sat[j] = *sat;
		data->sats[i].nsat = j + 1;
	}
	return 1;
}
