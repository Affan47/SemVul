engine_dynamic(void)
	{
	ENGINE *ret = ENGINE_new();
	if(!ret)
		return NULL;
	if(!ENGINE_set_id(ret, engine_dynamic_id) ||
			!ENGINE_set_name(ret, engine_dynamic_name) ||
			!ENGINE_set_init_function(ret, dynamic_init) ||
			!ENGINE_set_finish_function(ret, dynamic_finish) ||
			!ENGINE_set_ctrl_function(ret, dynamic_ctrl) ||
			!ENGINE_set_flags(ret, ENGINE_FLAGS_BY_ID_COPY) ||
			!ENGINE_set_cmd_defns(ret, dynamic_cmd_defns))
		{
		ENGINE_free(ret);
		return NULL;
		}
	return ret;
	}
