initialize_cc_devstate_map_helper(struct ast_config *cc_config, enum cc_state state, const char *cc_setting)
{
	const char *cc_devstate_str;
	enum ast_device_state this_devstate;

	if ((cc_devstate_str = ast_variable_retrieve(cc_config, "general", cc_setting))) {
		this_devstate = ast_devstate_val(cc_devstate_str);
		if (this_devstate != AST_DEVICE_UNKNOWN) {
			cc_state_to_devstate_map[state] = this_devstate;
		}
	}
}
