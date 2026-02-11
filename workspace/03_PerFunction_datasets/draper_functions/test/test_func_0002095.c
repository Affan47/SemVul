SC_SetPrefParamCommand(struct drxd_state *state,
				  u16 subCmd, u16 param0, u16 param1)
{
	int status;

	mutex_lock(&state->mutex);
	do {
		status = SC_WaitForReady(state);
		if (status < 0)
			break;
		status = Write16(state, SC_RA_RAM_CMD_ADDR__A, subCmd, 0);
		if (status < 0)
			break;
		status = Write16(state, SC_RA_RAM_PARAM1__A, param1, 0);
		if (status < 0)
			break;
		status = Write16(state, SC_RA_RAM_PARAM0__A, param0, 0);
		if (status < 0)
			break;

		status = SC_SendCommand(state, SC_RA_RAM_CMD_SET_PREF_PARAM);
		if (status < 0)
			break;
	} while (0);
	mutex_unlock(&state->mutex);
	return status;
}
