cc_generic_monitor_cancel_available_timer(struct ast_cc_monitor *monitor, int *sched_id)
{
	ast_assert(sched_id != NULL);

	if (*sched_id == -1) {
		return 0;
	}

	ast_log_dynamic_level(cc_logger_level, "Core %d: Canceling generic monitor available timer for monitor %s\n",
			monitor->core_id, monitor->interface->device_name);
	if (!ast_sched_del(cc_sched_context, *sched_id)) {
		cc_unref(monitor, "Remove scheduler's reference to the monitor");
	}
	*sched_id = -1;
	return 0;
}
