fil_node_complete_io(

	fil_node_t*	node,
	fil_system_t*	system,
	ulint		type)


{
	ut_ad(node);
	ut_ad(system);
	ut_ad(mutex_own(&(system->mutex)));

	ut_a(node->n_pending > 0);

	node->n_pending--;

	if (type == OS_FILE_WRITE) {
		system->modification_counter++;
		node->modification_counter = system->modification_counter;

		if (!node->space->is_in_unflushed_spaces) {

			node->space->is_in_unflushed_spaces = TRUE;
			UT_LIST_ADD_FIRST(unflushed_spaces,
					  system->unflushed_spaces,
					  node->space);
		}
	}

	if (node->n_pending == 0 && node->space->purpose == FIL_TABLESPACE
	    && node->space->id != 0) {

		UT_LIST_ADD_FIRST(LRU, system->LRU, node);
	}
}
