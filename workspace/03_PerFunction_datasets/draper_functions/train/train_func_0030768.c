kill_duplicate_offers(char *caller)
{
	unsigned long match_flags = MATCH_NO_REQUEST;
	struct ao2_iterator *dups_iter;


	dups_iter = ao2_t_callback_data(cc_core_instances, OBJ_MULTIPLE | OBJ_UNLINK,
		match_agent, caller, &match_flags, "Killing duplicate offers");
	if (dups_iter) {

		ao2_iterator_destroy(dups_iter);
	}
}
