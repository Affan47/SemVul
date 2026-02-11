dumb_remove_clicks_array(int n, DUMB_CLICK_REMOVER **cr, sample_t **samples, long length, float halflife)
{
	if (cr) {
		int i;
		for (i = 0; i < n >> 1; i++) {
			dumb_remove_clicks(cr[i << 1], samples[i], length, 2, halflife);
			dumb_remove_clicks(cr[(i << 1) + 1], samples[i] + 1, length, 2, halflife);
		}
		if (n & 1)
			dumb_remove_clicks(cr[i << 1], samples[i], length, 1, halflife);
	}
}
