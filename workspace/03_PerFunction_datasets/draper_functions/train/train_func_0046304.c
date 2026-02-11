handle_cli_ooh323_show_gk(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	char value[FORMAT_STRING_SIZE];

	switch (cmd) {
	case CLI_INIT:
		e->command = "ooh323 show gk";
		e->usage =
			"Usage: ooh323 show gk\n"
			"		 Shows Gatekeeper connection state\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 3)
		return CLI_SHOWUSAGE;

	ast_cli(a->fd, "\nGateKeeper connection state:\n");
	if (!gH323ep.gkClient) {
		ast_cli(a->fd, "No Gatekeeper is configured\n");
		return CLI_SUCCESS;
	}

	if (gRasGkMode == RasNoGatekeeper) {
		snprintf(value, sizeof(value), "%s", "No Gatekeeper");
	} else if (gRasGkMode == RasDiscoverGatekeeper) {
		snprintf(value, sizeof(value), "%s", "Discover");
	} else {
		snprintf(value, sizeof(value), "%s", gGatekeeper);
	}
	ast_cli(a->fd,  "%-20s%s\n", "Gatekeeper:", value);
	switch(gH323ep.gkClient->state) {
	case GkClientIdle:
		ast_cli(a->fd, "%-20s%s\n", "GK state:", "Idle");
		break;
	case GkClientDiscovered:
		ast_cli(a->fd, "%-20s%s\n", "GK state:", "Discovered");
		break;
	case GkClientRegistered:
		ast_cli(a->fd, "%-20s%s\n", "GK state:", "Registered");
		break;
	case GkClientUnregistered:
		ast_cli(a->fd, "%-20s%s\n", "GK state:", "Unregistered");
		break;
	case GkClientGkErr:
		ast_cli(a->fd, "%-20s%s\n", "GK state:", "Error");
		break;
	case GkClientFailed:
		ast_cli(a->fd, "%-20s%s\n", "GK state:", "Failed");
		break;
	default:
		break;
	}

	return CLI_SUCCESS;
}
