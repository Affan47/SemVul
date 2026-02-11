update_resource(auparse_state_t *au, const char *uuid, uid_t uid,
		time_t time, const char *name, int success, const char *reason,
		const char *res_type, const char *res)
{
	if (!is_resource(res) || !success)
		return 0;

	list_node_t *it;
	struct event *start = NULL;


	for (it = events->tail; it; it = it->prev) {
		start = it->data;
		if (start->type == ET_RES &&
		    start->success &&
		    start->uuid &&
		    strcmp(uuid, start->uuid) == 0 &&
		    strcmp(res_type, start->res_type) == 0 &&
		    strcmp(res, start->res) == 0)
			break;
	}
	if (it == NULL) {
		if (debug) {
			fprintf(stderr, "Couldn't find the correlated resource"
					" record to update.\n");
		}
		return 0;
	}

	start->end = time;
	add_proof(start, au);
	return 0;
}
