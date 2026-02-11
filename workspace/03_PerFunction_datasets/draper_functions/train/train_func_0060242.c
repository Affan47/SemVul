ctrl_get_cropcapdh(struct pvr2_ctrl *cptr, int *val)
{
	struct v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	int stat = pvr2_hdw_check_cropcap(cptr->hdw);
	if (stat != 0) {
		return stat;
	}
	*val = cap->defrect.height;
	return 0;
}
