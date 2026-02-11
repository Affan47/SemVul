write_ndx(int f, int32 ndx)
{
	static int32 prev_positive = -1, prev_negative = 1;
	int32 diff, cnt = 0;
	char b[6];

	if (protocol_version < 30 || read_batch) {
		write_int(f, ndx);
		return;
	}


	if (ndx >= 0) {
		diff = ndx - prev_positive;
		prev_positive = ndx;
	} else if (ndx == NDX_DONE) {
		*b = 0;
		write_buf(f, b, 1);
		return;
	} else {
		b[cnt++] = (char)0xFF;
		ndx = -ndx;
		diff = ndx - prev_negative;
		prev_negative = ndx;
	}


	if (diff < 0xFE && diff > 0)
		b[cnt++] = (char)diff;
	else if (diff < 0 || diff > 0x7FFF) {
		b[cnt++] = (char)0xFE;
		b[cnt++] = (char)((ndx >> 24) | 0x80);
		b[cnt++] = (char)ndx;
		b[cnt++] = (char)(ndx >> 8);
		b[cnt++] = (char)(ndx >> 16);
	} else {
		b[cnt++] = (char)0xFE;
		b[cnt++] = (char)(diff >> 8);
		b[cnt++] = (char)diff;
	}
	write_buf(f, b, cnt);
}
