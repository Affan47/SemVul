string2enum_state(const char *state)
{
	if (g_strcmp0(state, "offline") == 0)
		return CONNMAN_STATE_OFFLINE;
	else if (g_strcmp0(state, "idle") == 0)
		return CONNMAN_STATE_IDLE;
	else if (g_strcmp0(state, "ready") == 0)
		return CONNMAN_STATE_READY;
	else if (g_strcmp0(state, "online") == 0)
		return CONNMAN_STATE_ONLINE;
	else if (g_strcmp0(state, "failure") == 0)
		return CONNMAN_STATE_FAILURE;

	return CONNMAN_STATE_OFFLINE;
}
