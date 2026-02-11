matrox_accel_bmove(struct matrox_fb_info *minfo, int vxres, int sy,
			       int sx, int dy, int dx, int height, int width)
{
	int start, end;
	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	if ((dy < sy) || ((dy == sy) && (dx <= sx))) {
		mga_fifo(4);
		matrox_accel_restore_maccess(minfo);
		mga_outl(M_DWGCTL, M_DWG_BITBLT | M_DWG_SHIFTZERO | M_DWG_SGNZERO |
			 M_DWG_BFCOL | M_DWG_REPLACE);
		mga_outl(M_AR5, vxres);
		width--;
		start = sy*vxres+sx+curr_ydstorg(minfo);
		end = start+width;
	} else {
		mga_fifo(5);
		matrox_accel_restore_maccess(minfo);
		mga_outl(M_DWGCTL, M_DWG_BITBLT | M_DWG_SHIFTZERO | M_DWG_BFCOL | M_DWG_REPLACE);
		mga_outl(M_SGN, 5);
		mga_outl(M_AR5, -vxres);
		width--;
		end = (sy+height-1)*vxres+sx+curr_ydstorg(minfo);
		start = end+width;
		dy += height-1;
	}
	mga_fifo(6);
	matrox_accel_restore_maccess(minfo);
	mga_outl(M_AR0, end);
	mga_outl(M_AR3, start);
	mga_outl(M_FXBNDRY, ((dx+width)<<16) | dx);
	mga_ydstlen(dy, height);
	WaitTillIdle();

	CRITEND
}
