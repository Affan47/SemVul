rmsummary_assign_field(struct rmsummary *s, char *key, char *value)
{
	rmsummary_assign_as_string_field(s, key, value, command);
	rmsummary_assign_as_time_field  (s, key, value, start);
	rmsummary_assign_as_time_field  (s, key, value, end);
	rmsummary_assign_as_string_field(s, key, value, exit_type);
	rmsummary_assign_as_int_field   (s, key, value, signal);
	rmsummary_assign_as_string_field(s, key, value, limits_exceeded);
	rmsummary_assign_as_int_field   (s, key, value, exit_status);
	rmsummary_assign_as_time_field  (s, key, value, wall_time);
	rmsummary_assign_as_int_field   (s, key, value, max_concurrent_processes);
	rmsummary_assign_as_int_field   (s, key, value, total_processes);
	rmsummary_assign_as_time_field  (s, key, value, cpu_time);
	rmsummary_assign_as_int_field   (s, key, value, virtual_memory);
	rmsummary_assign_as_int_field   (s, key, value, resident_memory);
	rmsummary_assign_as_int_field   (s, key, value, swap_memory);
	rmsummary_assign_as_int_field   (s, key, value, bytes_read);
	rmsummary_assign_as_int_field   (s, key, value, bytes_written);
	rmsummary_assign_as_int_field   (s, key, value, workdir_num_files);
	rmsummary_assign_as_int_field   (s, key, value, workdir_footprint);

	return 0;
}
