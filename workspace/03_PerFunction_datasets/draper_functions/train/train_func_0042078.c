cc_extension_monitor_change_is_valid(struct cc_core_instance *core_instance, unsigned int parent_id, const char * const device_name, int is_valid)
{
	struct ast_cc_monitor *monitor_iter;
	struct extension_monitor_pvt *extension_pvt;
	struct extension_child_dialstring *child_dialstring;

	AST_LIST_TRAVERSE(core_instance->monitors, monitor_iter, next) {
		if (monitor_iter->id == parent_id) {
			break;
		}
	}

	if (!monitor_iter) {
		return;
	}
	extension_pvt = monitor_iter->private_data;

	AST_LIST_TRAVERSE(&extension_pvt->child_dialstrings, child_dialstring, next) {
		if (!strcmp(child_dialstring->device_name, device_name)) {
			child_dialstring->is_valid = is_valid;
			break;
		}
	}
}
