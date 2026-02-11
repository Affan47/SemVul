check_hmc_status(struct pluginDevice* dev)
{
	int status;
	char check_status[MAX_CMD_LEN];
	char* output = NULL;
	int rc = S_OK;

	if(Debug){
		LOG(PIL_DEBUG, "%s: called, hmc=%s\n", __FUNCTION__, dev->hmc);
	}

	snprintf(check_status, MAX_CMD_LEN
	,	SSH_CMD " -l " HMCROOT " %s lshmc -r -F ssh", dev->hmc);
	if(Debug){
		LOG(PIL_DEBUG, "%s: check_status %s\n", __FUNCTION__
		,	check_status);
	}

	output = do_shell_cmd(check_status, &status, dev->password);
	if (Debug) {
		LOG(PIL_DEBUG, "%s: status=%d, output=%s\n", __FUNCTION__
		,	status, output ? output : "(nil)");
	}

	if (NULL == output || strncmp(output, "enable", 6) != 0) {
		rc = S_BADCONFIG;
	}
	if (NULL != output) {
		FREE(output);
	}
	return rc;
}
