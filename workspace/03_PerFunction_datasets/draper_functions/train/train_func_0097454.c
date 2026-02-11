sync_array_validate(

	sync_array_t*	arr)
{
	ulint		i;
	sync_cell_t*	cell;
	ulint		count		= 0;

	sync_array_enter(arr);

	for (i = 0; i < arr->n_cells; i++) {
		cell = sync_array_get_nth_cell(arr, i);
		if (cell->wait_object != NULL) {
			count++;
		}
	}

	ut_a(count == arr->n_reserved);

	sync_array_exit(arr);
}
