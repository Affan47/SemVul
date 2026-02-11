ct_describe_cmd_state(CS_INT state)
{
	tdsdump_log(TDS_DBG_FUNC, "ct_describe_cmd_state(%d)\n", state);

	switch (state) {
	case _CS_COMMAND_IDLE:
		return "IDLE";
	case _CS_COMMAND_BUILDING:
		return "BUILDING";
	case _CS_COMMAND_READY:
		return "READY";
	case _CS_COMMAND_SENT:
		return "SENT";
	}
	return "???";
}
