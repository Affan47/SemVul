GetActiveCalls(gn_data *data, struct gn_statemachine *state)
{
	if (DRVINSTANCE(state)->capabilities & NK6100_CAP_OLD_CALL_API)
		return GN_ERR_NOTSUPPORTED;
	else
		return GetActiveCalls1(data, state);
}
