e_config_target_changed (EConfig *config,
                         e_config_target_change_t how)
{
	if (how == E_CONFIG_TARGET_CHANGED_REBUILD) {
		g_idle_add (ec_idle_handler_for_rebuild, config);
	} else {
		ec_call_page_check (config);
	}


}
