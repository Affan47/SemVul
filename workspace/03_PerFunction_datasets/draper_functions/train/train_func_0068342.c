_print_part_priority_normalized(priority_factors_object_t * job, int width,
				    bool right, char* suffix)
{
	if (job == NULL)
		_print_str("PARTITION", width, right, true);
	else if (job == (priority_factors_object_t *) -1)
		_print_int(weight_part, width, right, true);
	else {
		double num = 0;
		if (weight_part)
			num = job->priority_part / weight_part;
		_print_norm(num, width, right, true);
	}

	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
