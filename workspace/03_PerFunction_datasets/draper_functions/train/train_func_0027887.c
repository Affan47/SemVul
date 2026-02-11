_print_reservation(reserve_info_t *resv_ptr, int width)
{
	char format[64], tmp1[32], tmp2[32], tmp3[32];
	char *state = "INACTIVE";
	uint32_t duration;
	time_t now = time(NULL);

	slurm_make_time_str(&resv_ptr->start_time, tmp1, sizeof(tmp1));
	slurm_make_time_str(&resv_ptr->end_time,   tmp2, sizeof(tmp2));
	duration = difftime(resv_ptr->end_time, resv_ptr->start_time);
	secs2time_str(duration, tmp3, sizeof(tmp3));

	if ((resv_ptr->start_time <= now) && (resv_ptr->end_time >= now))
		state = "ACTIVE";
	snprintf(format, sizeof(format),
		 "%%-%ds  %%8s  %%19s  %%19s  %%11s  %%s\n", width);
	printf(format,
	       resv_ptr->name, state, tmp1, tmp2, tmp3, resv_ptr->node_list);

	return;
}
