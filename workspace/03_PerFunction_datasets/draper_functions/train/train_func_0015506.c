unregister_stat_tracer(struct tracer_stat *trace)
{
	struct stat_session *node, *tmp;

	mutex_lock(&all_stat_sessions_mutex);
	list_for_each_entry_safe(node, tmp, &all_stat_sessions, session_list) {
		if (node->ts == trace) {
			list_del(&node->session_list);
			destroy_session(node);
			break;
		}
	}
	mutex_unlock(&all_stat_sessions_mutex);
}
