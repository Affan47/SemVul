get_nm_state (NMClient *client)
{
	NMState state;
	char *state_string;
	gboolean success = TRUE;

	state = nm_client_get_state (client);

	switch (state) {
	case NM_STATE_ASLEEP:
		state_string = "asleep";
		break;
	case NM_STATE_CONNECTING:
		state_string = "connecting";
		break;
	case NM_STATE_CONNECTED_LOCAL:
		state_string = "connected (local only)";
		break;
	case NM_STATE_CONNECTED_SITE:
		state_string = "connected (site only)";
		break;
	case NM_STATE_CONNECTED_GLOBAL:
		state_string = "connected (global)";
		break;
	case NM_STATE_DISCONNECTED:
		state_string = "disconnected";
		break;
	case NM_STATE_UNKNOWN:
	default:
		state_string = "unknown";
		success = FALSE;
		break;
	}

	printf ("State: %s\n\n", state_string);

	return success;
}
