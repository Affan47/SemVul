set_station_helper(uint8_t * b, const char * callsign, int freq) {
	char tmp[FREQ_WIDTH+1];
	uint8_t * bm = b + CALL_WIDTH;
	uint8_t * bf = b;

	int j,i;

	if (freq > IFP_FREQ_MAX || freq < IFP_FREQ_MIN) {

		return IFP_ERR_BAD_FREQUENCY;
	}
	i = snprintf(tmp, FREQ_WIDTH+1, "%03d.%02d", freq/100, freq%100);
	if (i != FREQ_WIDTH || tmp[3] != '.') {
		ifp_err("(internal) formatting error for freq=%d. i=%d, tmp[3]=%d",
			freq, i, (int)tmp[3]);
	}
	for (j=0; j!=FREQ_WIDTH; j++) {
		if (tmp[j] != '.') {
			tmp[j] -= '0';
		}
	}
	memcpy(bf, tmp, FREQ_WIDTH);

	memset(bm, '\0', CALL_WIDTH);
	strncpy(bm, callsign, CALL_WIDTH);

	return 0;
}
