cc_monitor_failed(void *data)
{
	struct ast_cc_monitor_failure_data *failure_data = data;
	struct cc_core_instance *core_instance;
	struct ast_cc_monitor *monitor_iter;

	core_instance = find_cc_core_instance(failure_data->core_id);
	if (!core_instance) {

		ast_log_dynamic_level(cc_logger_level,
			"Core %d: Could not find core instance for device %s '%s'\n",
			failure_data->core_id, failure_data->device_name, failure_data->debug);
		ast_free((char *) failure_data->device_name);
		ast_free((char *) failure_data->debug);
		ast_free(failure_data);
		return -1;
	}

	AST_LIST_LOCK(core_instance->monitors);
	AST_LIST_TRAVERSE_SAFE_BEGIN(core_instance->monitors, monitor_iter, next) {
		if (monitor_iter->interface->monitor_class == AST_CC_DEVICE_MONITOR) {
			if (!strcmp(monitor_iter->interface->device_name, failure_data->device_name)) {
				AST_LIST_REMOVE_CURRENT(next);
				cc_extension_monitor_change_is_valid(core_instance, monitor_iter->parent_id,
						monitor_iter->interface->device_name, 1);
				monitor_iter->callbacks->cancel_available_timer(monitor_iter, &monitor_iter->available_timer_id);
				manager_event(EVENT_FLAG_CC, "CCMonitorFailed",
					"CoreID: %d\r\n"
					"Callee: %s\r\n",
					monitor_iter->core_id, monitor_iter->interface->device_name);
				cc_unref(monitor_iter, "Monitor reported failure. Unref list's reference.");
			}
		}
	}
	AST_LIST_TRAVERSE_SAFE_END;

	if (!has_device_monitors(core_instance)) {
		ast_cc_failed(core_instance->core_id, "All monitors have failed\n");
	}
	AST_LIST_UNLOCK(core_instance->monitors);
	cc_unref(core_instance, "Finished with core_instance in cc_monitor_failed\n");

	ast_free((char *) failure_data->device_name);
	ast_free((char *) failure_data->debug);
	ast_free(failure_data);
	return 0;
}
