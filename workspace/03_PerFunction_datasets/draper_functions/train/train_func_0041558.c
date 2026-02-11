dump_queue_members(struct call_queue *pm_queue)
{
	struct member *cur_member;
	struct ast_str *value;
	struct ao2_iterator mem_iter;

	if (!pm_queue) {
		return;
	}


	if (!(value = ast_str_create(4096))) {
		return;
	}

	mem_iter = ao2_iterator_init(pm_queue->members, 0);
	while ((cur_member = ao2_iterator_next(&mem_iter))) {
		if (!cur_member->dynamic) {
			ao2_ref(cur_member, -1);
			continue;
		}

		ast_str_append(&value, 0, "%s%s;%d;%d;%s;%s",
			ast_str_strlen(value) ? "|" : "",
			cur_member->interface,
			cur_member->penalty,
			cur_member->paused,
			cur_member->membername,
			cur_member->state_interface);

		ao2_ref(cur_member, -1);
	}
	ao2_iterator_destroy(&mem_iter);

	if (ast_str_strlen(value) && !cur_member) {
		if (ast_db_put(pm_family, pm_queue->name, ast_str_buffer(value))) {
			ast_log(LOG_WARNING, "failed to create persistent dynamic entry!\n");
		}
	} else {

		ast_db_del(pm_family, pm_queue->name);
	}

	ast_free(value);
}
