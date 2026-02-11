qib_sd7220_prog_vfy(struct qib_devdata *dd, int sdnum,
			       const u8 *img, int len, int offset)
{
	int cnt, sofar, req, idx, errors;
	unsigned char readback[VFY_CHUNK];

	errors = 0;
	sofar = 0;
	while (sofar < len) {
		req = len - sofar;
		if (req > VFY_CHUNK)
			req = VFY_CHUNK;
		cnt = qib_sd7220_ram_xfer(dd, sdnum, sofar + offset,
					  readback, req, 1);
		if (cnt < req) {

			sofar = -1;
			break;
		}
		for (idx = 0; idx < cnt; ++idx) {
			if (readback[idx] != img[idx+sofar])
				++errors;
		}
		sofar += cnt;
	}
	return errors ? -errors : sofar;
}
