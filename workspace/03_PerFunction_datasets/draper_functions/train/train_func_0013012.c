string2state(const char *state)
{
	if (state == NULL)
		return G_SUPPLICANT_STATE_UNKNOWN;

	if (g_str_equal(state, "unknown") == TRUE)
		return G_SUPPLICANT_STATE_UNKNOWN;
	else if (g_str_equal(state, "interface_disabled") == TRUE)
		return G_SUPPLICANT_STATE_DISABLED;
	else if (g_str_equal(state, "disconnected") == TRUE)
		return G_SUPPLICANT_STATE_DISCONNECTED;
	else if (g_str_equal(state, "inactive") == TRUE)
		return G_SUPPLICANT_STATE_INACTIVE;
	else if (g_str_equal(state, "scanning") == TRUE)
		return G_SUPPLICANT_STATE_SCANNING;
	else if (g_str_equal(state, "authenticating") == TRUE)
		return G_SUPPLICANT_STATE_AUTHENTICATING;
	else if (g_str_equal(state, "associating") == TRUE)
		return G_SUPPLICANT_STATE_ASSOCIATING;
	else if (g_str_equal(state, "associated") == TRUE)
		return G_SUPPLICANT_STATE_ASSOCIATED;
	else if (g_str_equal(state, "group_handshake") == TRUE)
		return G_SUPPLICANT_STATE_GROUP_HANDSHAKE;
	else if (g_str_equal(state, "4way_handshake") == TRUE)
		return G_SUPPLICANT_STATE_4WAY_HANDSHAKE;
	else if (g_str_equal(state, "completed") == TRUE)
		return G_SUPPLICANT_STATE_COMPLETED;

	return G_SUPPLICANT_STATE_UNKNOWN;
}
