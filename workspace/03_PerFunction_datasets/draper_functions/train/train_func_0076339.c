print_steps_array(job_step_info_t * steps, int size, List format)
{

	if (!params.no_header)
		print_step_from_format(NULL, format);

	if (size > 0) {
		int i;
		List step_list;
		ListIterator step_iterator;
		job_step_info_t *step_ptr;

		step_list = list_create(NULL);


		for (i = 0; i < size; i++) {
			if (_filter_step(&steps[i]))
				continue;
			list_append(step_list, (void *) &steps[i]);
		}

		sort_step_list(step_list);


		step_iterator = list_iterator_create(step_list);
		while ((step_ptr = list_next(step_iterator))) {
			print_step_from_format(step_ptr, format);
		}
		list_iterator_destroy(step_iterator);
		list_destroy(step_list);
	}

	return SLURM_SUCCESS;
}
