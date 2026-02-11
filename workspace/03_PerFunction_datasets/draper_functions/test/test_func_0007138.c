mxl1x1sf_demod_get_sync_lock_status(struct mxl111sf_demod_state *state,
					int *sync_lock)
{
	u8 val = 0;
	int ret = mxl111sf_demod_read_reg(state, V6_SYNC_LOCK_REG, &val);
	if (mxl_fail(ret))
		goto fail;
	*sync_lock = (val & SYNC_LOCK_MASK) >> 4;
fail:
	return ret;
}
