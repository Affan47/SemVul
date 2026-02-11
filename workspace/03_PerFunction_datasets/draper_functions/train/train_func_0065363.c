cyttsp_handshake(struct cyttsp *ts)
{
	if (ts->pdata->use_hndshk)
		return ttsp_send_command(ts,
				ts->xy_data.hst_mode ^ CY_HNDSHK_BIT);

	return 0;
}
