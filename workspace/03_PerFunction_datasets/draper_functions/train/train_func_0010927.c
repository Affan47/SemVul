gfarm_auth_config_add(
	enum gfarm_auth_config_command command,
	enum gfarm_auth_method method,
	struct gfarm_hostspec *hsp)
{
	struct gfarm_auth_config *acp;

	GFARM_MALLOC(acp);
	if (acp == NULL) {
		gflog_debug(GFARM_MSG_1000903,
			"allocation of 'gfarm_auth_config' failed");
		return (GFARM_ERR_NO_MEMORY);
	}
	acp->next = NULL;
	acp->command = command;
	acp->method = method;
	acp->hostspec = hsp;

	*gfarm_auth_config_last = acp;
	gfarm_auth_config_last = &acp->next;
	return (GFARM_ERR_NO_ERROR);
}
