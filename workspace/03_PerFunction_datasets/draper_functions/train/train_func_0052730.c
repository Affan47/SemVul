fil_node_prepare_for_io(

	fil_node_t*	node,
	fil_system_t*	system,
	fil_space_t*	space)
{
	ut_ad(node && system && space);
	ut_ad(mutex_own(&(system->mutex)));

	if (system->n_open > system->max_n_open + 5) {
		ut_print_timestamp(stderr);
		fprintf(stderr,
			"  InnoDB: Warning: open files %lu"
			" exceeds the limit %lu\n",
			(ulong) system->n_open,
			(ulong) system->max_n_open);
	}

	if (node->open == FALSE) {

		ut_a(node->n_pending == 0);

		fil_node_open_file(node, system, space);
	}

	if (node->n_pending == 0 && space->purpose == FIL_TABLESPACE
	    && space->id != 0) {


		ut_a(UT_LIST_GET_LEN(system->LRU) > 0);

		UT_LIST_REMOVE(LRU, system->LRU, node);
	}

	node->n_pending++;
}
