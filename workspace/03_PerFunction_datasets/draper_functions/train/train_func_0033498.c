feature_check(struct ast_channel *chan, struct ast_flags *features, char *code) {
	char *chan_dynamic_features;
	ast_channel_lock(chan);
	chan_dynamic_features = ast_strdupa(S_OR(pbx_builtin_getvar_helper(chan, "DYNAMIC_FEATURES"),""));
	ast_channel_unlock(chan);

	return feature_interpret_helper(chan, NULL, NULL, code, 0, chan_dynamic_features, features, FEATURE_INTERPRET_CHECK, NULL);
}
