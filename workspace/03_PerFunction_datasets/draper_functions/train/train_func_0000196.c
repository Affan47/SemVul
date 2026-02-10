rhcs_parse_config_info(struct pluginDevice* sd, StonithNVpair * info)
{
	char * 		key;
	char *		value;
	StonithNVpair *	nv;

	sd->hostlist = NULL;
	sd->cmd_opts = g_hash_table_new(g_str_hash, g_str_equal);


	for (nv = info; nv->s_name; nv++) {
		if (!nv->s_name || !nv->s_value) {
			continue;
		}
		key = STRDUP(nv->s_name);
		if (!key) {
			goto err_mem;
		}
		value = STRDUP(nv->s_value);
		if (!value) {
			FREE(key);
			goto err_mem;
		}
		if (!strcmp(key,"hostlist")) {
			sd->hostlist = value;
			FREE(key);
		} else {
			g_hash_table_insert(sd->cmd_opts, key, value);
		}
	}

	return(S_OK);

err_mem:
	LOG(PIL_CRIT, "%s: out of memory!", __FUNCTION__);
	rhcs_unconfig(sd);

	return(S_OOPS);
}
