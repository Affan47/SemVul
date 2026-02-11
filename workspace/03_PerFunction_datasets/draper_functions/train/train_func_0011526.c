get_object_details(void)
{
	uint32_t i;
	struct object_entry **sorted_by_offset;

	sorted_by_offset = xcalloc(nr_objects, sizeof(struct object_entry *));
	for (i = 0; i < nr_objects; i++)
		sorted_by_offset[i] = objects + i;
	qsort(sorted_by_offset, nr_objects, sizeof(*sorted_by_offset), pack_offset_sort);

	for (i = 0; i < nr_objects; i++)
		check_object(sorted_by_offset[i]);

	free(sorted_by_offset);
}
