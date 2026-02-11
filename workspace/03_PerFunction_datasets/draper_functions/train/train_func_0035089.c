pvr2_hdw_check_cropcap(struct pvr2_hdw *hdw)
{
	if (!hdw->cropcap_stale) {
		return 0;
	}
	pvr2_hdw_status_poll(hdw);
	if (hdw->cropcap_stale) {
		return -EIO;
	}
	return 0;
}
