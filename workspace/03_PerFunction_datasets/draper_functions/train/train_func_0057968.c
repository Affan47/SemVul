sync_leaders(int me, int n, int *leaders, struct _gps *wgps, float8 *skew)
{
	int		i;

	if (me == 0) {


		*skew = 0.0;

		for (i = 1; i < n; i++) {
			if (sync_master(wgps, wgps + leaders[i], NSYNCS))
				return(LAMERROR);
		}
	} else {


		if (sync_slave(wgps, wgps + me, skew, NSYNCS))
			return(LAMERROR);
	}

	return(0);
}
