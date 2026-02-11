external_get_confignames(StonithPlugin* p)
{
  	struct pluginDevice *	sd;
	const char *		op = "getconfignames";
	int 			i, rc;

	if (Debug) {
		LOG(PIL_DEBUG, "%s: called.", __FUNCTION__);
	}

	sd = (struct pluginDevice *)p;

	if (sd->subplugin != NULL) {

		char	*output = NULL, *pch;
		int	namecount;

		rc = external_run_cmd(sd, op, &output);
		if (rc != 0) {
			LOG(PIL_CRIT, "%s: '%s %s' failed with rc %d",
				__FUNCTION__, sd->subplugin, op, rc);
			if (output) {
				LOG(PIL_CRIT, "plugin output: %s", output);
				FREE(output);
			}
			return NULL;
		}
		if (Debug) {
			LOG(PIL_DEBUG, "%s: '%s %s' returned %d",
				__FUNCTION__, sd->subplugin, op, rc);
			if (output) {
				LOG(PIL_DEBUG, "plugin output: %s", output);
			}
		}

		namecount = get_num_tokens(output);
		sd->confignames = (char **)MALLOC((namecount+1)*sizeof(char *));
		if (sd->confignames == NULL) {
			LOG(PIL_CRIT, "%s: out of memory", __FUNCTION__);
			if (output) { FREE(output); }
			return NULL;
		}


		pch = strtok(output, WHITESPACE);
		for (i = 0; i < namecount; i++) {
			if (Debug) {
				LOG(PIL_DEBUG, "%s: %s configname %s",
					__FUNCTION__, sd->subplugin, pch);
			}
			sd->confignames[i] = STRDUP(pch);
			pch = strtok(NULL, WHITESPACE);
		}
		FREE(output);
		sd->confignames[namecount] = NULL;
	}else{

		struct dirent **	files = NULL;
		int			dircount;


		dircount = scandir(STONITH_EXT_PLUGINDIR, &files,
				SCANSEL_CAST exec_select, NULL);
		if (dircount < 0) {
			return NULL;
		}

		sd->confignames = (char **)MALLOC((dircount+1)*sizeof(char *));
		if (!sd->confignames) {
			LOG(PIL_CRIT, "%s: out of memory", __FUNCTION__);
			return NULL;
		}

		for (i = 0; i < dircount; i++) {
			sd->confignames[i] = STRDUP(files[i]->d_name);
			free(files[i]);
			files[i] = NULL;
		}
		free(files);
		sd->confignames[dircount] = NULL;
	}

	return (const char * const *)sd->confignames;
}
