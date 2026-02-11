_print_root(sinfo_data_t * sinfo_data, int width,
			bool right_justify, char *suffix)
{
	if (sinfo_data) {
		if (sinfo_data->part_info == NULL)
			_print_str("n/a", width, right_justify, true);
		else if (sinfo_data->part_info->flags & PART_FLAG_ROOT_ONLY)
			_print_str("yes", width, right_justify, true);
		else
			_print_str("no", width, right_justify, true);
	} else
		_print_str("ROOT", width, right_justify, true);

	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
