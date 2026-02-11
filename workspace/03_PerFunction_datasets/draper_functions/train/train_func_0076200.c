orinoco_get_bitratemode(int bitrate, int automatic)
{
	int ratemode = -1;
	int i;

	if ((bitrate != 10) && (bitrate != 20) &&
	    (bitrate != 55) && (bitrate != 110))
		return ratemode;

	for (i = 0; i < BITRATE_TABLE_SIZE; i++) {
		if ((bitrate_table[i].bitrate == bitrate) &&
		    (bitrate_table[i].automatic == automatic)) {
			ratemode = i;
			break;
		}
	}
	return ratemode;
}
