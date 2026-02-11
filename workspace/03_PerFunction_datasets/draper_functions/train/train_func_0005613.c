featuremap_write(struct ast_channel *chan, const char *cmd, char *data,
		const char *value)
{
	struct feature_ds *feature_ds;
	struct feature_exten *fe;

	if (!ast_find_call_feature(data)) {
		ast_log(LOG_WARNING, "Invalid argument '%s' to FEATUREMAP()\n", data);
		return -1;
	}

	ast_channel_lock(chan);

	if (!(feature_ds = get_feature_ds(chan))) {
		ast_channel_unlock(chan);
		return -1;
	}

	if (!(fe = ao2_find(feature_ds->feature_map, data, OBJ_KEY))) {
		if (!(fe = ao2_alloc(sizeof(*fe), NULL))) {
			ast_channel_unlock(chan);
			return -1;
		}
		ast_copy_string(fe->sname, data, sizeof(fe->sname));
		ao2_link(feature_ds->feature_map, fe);
	}

	ast_channel_unlock(chan);

	ao2_lock(fe);
	ast_copy_string(fe->exten, value, sizeof(fe->exten));
	ao2_unlock(fe);
	ao2_ref(fe, -1);
	fe = NULL;

	return 0;
}
