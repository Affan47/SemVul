dvbt_start(struct drxk_state *state)
{
	u16 param1;
	int status;


	dprintk(1, "\n");


	param1 = OFDM_SC_RA_RAM_LOCKTRACK_MIN;
	status = dvbt_sc_command(state, OFDM_SC_RA_RAM_CMD_PROC_START, 0,
				 OFDM_SC_RA_RAM_SW_EVENT_RUN_NMASK__M, param1,
				 0, 0, 0);
	if (status < 0)
		goto error;

	status = mpegts_start(state);
	if (status < 0)
		goto error;
	status = write16(state, FEC_COMM_EXEC__A, FEC_COMM_EXEC_ACTIVE);
	if (status < 0)
		goto error;
error:
	if (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	return status;
}
