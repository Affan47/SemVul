cc_core_instance_destructor(void *data)
{
	struct cc_core_instance *core_instance = data;
	ast_log_dynamic_level(cc_logger_level, "Core %d: Destroying core instance\n", core_instance->core_id);
	if (core_instance->agent) {
		cc_unref(core_instance->agent, "Core instance is done with the agent now");
	}
	if (core_instance->monitors) {
		core_instance->monitors = cc_unref(core_instance->monitors, "Core instance is done with interface list");
	}
}
