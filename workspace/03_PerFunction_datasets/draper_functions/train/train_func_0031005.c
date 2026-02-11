cc_stop_ringing(void *data)
{
	struct cc_core_instance *core_instance = data;
	int res = 0;

	if (core_instance->agent->callbacks->stop_ringing) {
		res = core_instance->agent->callbacks->stop_ringing(core_instance->agent);
	}


	ast_cc_monitor_request_acked(core_instance->core_id, "Agent %s asked to stop ringing. Be prepared to be recalled again.",
			core_instance->agent->device_name);
	cc_unref(core_instance, "Stop ringing finished. Unref core_instance");
	return res;
}
