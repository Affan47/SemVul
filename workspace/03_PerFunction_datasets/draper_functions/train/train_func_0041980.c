MtxOrb_set_char (Driver *drvthis, int n, unsigned char *dat)
{
	PrivateData *p = drvthis->private_data;
	unsigned char out[12] = { '\xFE', 'N', 0, 0,0,0,0,0,0,0,0 };
	unsigned char mask = (1 << p->cellwidth) - 1;
	int row;

	if ((n < 0) || (n >= NUM_CCs))
		return;
	if (!dat)
		return;

	out[2] = n;

	for (row = 0; row < p->cellheight; row++) {
		out[row+3] = dat[row] & mask;
	}
	write(p->fd, out, 11);
}
