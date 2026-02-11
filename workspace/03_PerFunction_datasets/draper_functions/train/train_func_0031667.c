print_sinfo_entry(sinfo_data_t *sinfo_data)
{
	ListIterator i = list_iterator_create(params.format_list);
	sinfo_format_t *current;

	while ((current = (sinfo_format_t *) list_next(i)) != NULL) {
		if (current->function(sinfo_data, current->width,
				      current->right_justify, current->suffix)
		    != SLURM_SUCCESS)
			return SLURM_ERROR;
	}
	list_iterator_destroy(i);

	printf("\n");
	return SLURM_SUCCESS;
}
