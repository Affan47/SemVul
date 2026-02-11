sync_arr_wake_threads_if_sema_free(void)

{
	sync_array_t*	arr	= sync_primary_wait_array;
	sync_cell_t*	cell;
	ulint		count;
	ulint		i;
	os_event_t      event;

	sync_array_enter(arr);

	i = 0;
	count = 0;

	while (count < arr->n_reserved) {

		cell = sync_array_get_nth_cell(arr, i);
		i++;

		if (cell->wait_object == NULL) {
			continue;
		}
			count++;

			if (sync_arr_cell_can_wake_up(cell)) {

			event = sync_cell_get_event(cell);

			os_event_set(event);
		}

	}

	sync_array_exit(arr);
}
