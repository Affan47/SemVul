quorum_notification_fn(
	quorum_handle_t handle,
	uint32_t quorate,
	uint64_t ring_id,
	uint32_t view_list_entries,
	uint32_t *view_list)
{
	int i;

	printf("quorum notification called \n");
	printf("  quorate   = %lu\n", (long unsigned int) quorate);
	printf("  ring id   = %llu\n", (long long unsigned int) ring_id);
	printf("  num nodes = %lu ", (long unsigned int) view_list_entries);

	for (i=0; i<view_list_entries; i++) {
		printf(" %d ", view_list[i]);
	}
	printf("\n");
}
