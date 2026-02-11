fil_space_get_size(

	ulint	id)
{
	fil_node_t*	node;
	fil_space_t*	space;
	ulint		size;

	ut_ad(fil_system);

	mutex_enter(&fil_system->mutex);

	space = fil_space_get_by_id(id);

	if (space == NULL) {
		mutex_exit(&fil_system->mutex);

		return(0);
	}

	if (space->size == 0 && space->purpose == FIL_TABLESPACE) {
		ut_a(id != 0);

		ut_a(1 == UT_LIST_GET_LEN(space->chain));

		mutex_exit(&fil_system->mutex);


		fil_mutex_enter_and_prepare_for_io(id);


		space = fil_space_get_by_id(id);

		if (space == NULL) {
			mutex_exit(&fil_system->mutex);
			return(0);
		}

		node = UT_LIST_GET_FIRST(space->chain);


		fil_node_prepare_for_io(node, fil_system, space);
		fil_node_complete_io(node, fil_system, OS_FILE_READ);
	}

	size = space->size;

	mutex_exit(&fil_system->mutex);

	return(size);
}
