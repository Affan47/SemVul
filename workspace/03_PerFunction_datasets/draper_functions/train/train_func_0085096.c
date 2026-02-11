CFontzPacket_set_char (Driver *drvthis, int n, unsigned char *dat)
{
	PrivateData *p = drvthis->private_data;
	unsigned char out[9];
	unsigned char mask = (1 << p->cellwidth) - 1;
	int row;

	if ((n < 0) || (n >= NUM_CCs) || (!dat))
		return;


	if ((p->model_desc->flags & CFA_HAS_KS0073) && (p->ccmode != bignum))
		dat[p->cellheight-1] = 0;

	out[0] = n;
	for (row = 0; row < p->cellheight; row++) {
		out[row+1] = dat[row] & mask;
	}
	send_bytes_message(p->fd, CF633_Set_LCD_Special_Character_Data, 9, out);
}
