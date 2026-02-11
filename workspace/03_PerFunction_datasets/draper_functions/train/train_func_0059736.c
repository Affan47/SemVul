nsupdate_exec(nsupdate_params_t *params)
{
	if (!params) {
		return KNOT_EINVAL;
	}

	int ret = KNOT_EOK;


	if (EMPTY_LIST(params->qfiles)) {
		return nsupdate_process(params, stdin);
	}


	strnode_t *n = NULL;
	WALK_LIST(n, params->qfiles) {
		if (strcmp(n->str, "-") == 0) {
			ret = nsupdate_process(params, stdin);
			continue;
		}
		FILE *fp = fopen(n->str, "r");
		if (!fp) {
			ERR("could not open '%s': %s\n",
			    n->str, strerror(errno));
			return KNOT_ERROR;
		}
		ret = nsupdate_process(params, fp);
		fclose(fp);
	}

	return ret;
}
