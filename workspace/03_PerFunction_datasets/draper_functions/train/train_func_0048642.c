cb_status__normal(
	const char *path, unsigned int status_flags, void *payload)
{
	status_entry_counts *counts = payload;

	if (counts->entry_count >= counts->expected_entry_count) {
		counts->wrong_status_flags_count++;
		goto exit;
	}

	if (strcmp(path, counts->expected_paths[counts->entry_count])) {
		counts->wrong_sorted_path++;
		goto exit;
	}

	if (status_flags != counts->expected_statuses[counts->entry_count])
		counts->wrong_status_flags_count++;

exit:
	counts->entry_count++;
	return 0;
}
