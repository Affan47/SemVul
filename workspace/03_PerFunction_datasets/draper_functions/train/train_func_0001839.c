cmd_set_color_curve(SANE_Handle handle, unsigned char col)
{

	KodakAio_Scanner *s = (KodakAio_Scanner *) handle;
	SANE_Status status = SANE_STATUS_GOOD;
	unsigned char tx_col[8];
	unsigned char rx[8];
	unsigned char tx_curve[256];
	unsigned char i;
	DBG(32, "%s: start\n", __func__);
	tx_col[0]=0x1b; tx_col[1]='S'; tx_col[2]='K'; tx_col[3]=col; tx_col[4]=0; tx_col[5]=0; tx_col[6]=0; tx_col[7]=0;

	for(i=0;i<255;++i) tx_curve[i]=i;
	k_send(s, tx_col, 8, &status);
	if (status != SANE_STATUS_GOOD) {
		DBG(32, "%s: tx err, %s\n", __func__, "curve command");
		return status;
	}
	k_send(s, tx_curve, 256, &status);
	if (status != SANE_STATUS_GOOD) {
		DBG(32, "%s: tx err, %s\n", __func__, "curve data");
		return status;
	}
	if (kodakaio_expect_ack(s, rx) != SANE_STATUS_GOOD) return SANE_STATUS_IO_ERROR;
		DBG(10, "%s: sent curve OK, \n", __func__);
		return status;
}
