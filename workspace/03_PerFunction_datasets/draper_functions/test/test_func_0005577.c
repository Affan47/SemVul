ast_cc_get_monitor_by_recall_core_id(const int core_id, const char * const device_name)
{
	struct cc_core_instance *core_instance = find_cc_core_instance(core_id);
	struct ast_cc_monitor *monitor_iter;

	if (!core_instance) {
		return NULL;
	}

	AST_LIST_LOCK(core_instance->monitors);
	AST_LIST_TRAVERSE(core_instance->monitors, monitor_iter, next) {
		if (!strcmp(monitor_iter->interface->device_name, device_name)) {

			cc_ref(monitor_iter, "Hand the requester of the monitor a reference");
			break;
		}
	}
	AST_LIST_UNLOCK(core_instance->monitors);
	cc_unref(core_instance, "Done with core instance ref in ast_cc_get_monitor_by_recall_core_id");
	return monitor_iter;
}
