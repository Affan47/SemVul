mxl111sf_ep4_streaming_ctrl(struct dvb_frontend *fe, int onoff)
{
	struct mxl111sf_state *state = fe_to_priv(fe);
	int ret = 0;

	pr_debug("%s(%d)\n", __func__, onoff);

	if (onoff) {
		ret = mxl111sf_enable_usb_output(state);
		mxl_fail(ret);
	}

	return ret;
}
