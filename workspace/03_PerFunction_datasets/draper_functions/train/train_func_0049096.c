pvr2_hdw_get_cropcap(struct pvr2_hdw *hdw, struct v4l2_cropcap *pp)
{
	int stat = 0;
	LOCK_TAKE(hdw->big_lock);
	stat = pvr2_hdw_check_cropcap(hdw);
	if (!stat) {
		memcpy(pp, &hdw->cropcap_info, sizeof(hdw->cropcap_info));
	}
	LOCK_GIVE(hdw->big_lock);
	return stat;
}
