get_member_penalty(char *queuename, char *interface)
{
	int foundqueue = 0, penalty;
	struct call_queue *q, tmpq = {
		.name = queuename,
	};
	struct member *mem;

	if ((q = ao2_t_find(queues, &tmpq, OBJ_POINTER, "Search for queue"))) {
		foundqueue = 1;
		ao2_lock(q);
		if ((mem = interface_exists(q, interface))) {
			penalty = mem->penalty;
			ao2_ref(mem, -1);
			ao2_unlock(q);
			queue_t_unref(q, "Search complete");
			return penalty;
		}
		ao2_unlock(q);
		queue_t_unref(q, "Search complete");
	}


	if (foundqueue) {
		ast_log (LOG_ERROR, "Invalid queuename\n");
	} else {
		ast_log (LOG_ERROR, "Invalid interface\n");
	}

	return RESULT_FAILURE;
}
