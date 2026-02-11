merge__dump_index_entries(git_vector *index_entries)
{
	size_t i;
	const git_index_entry *index_entry;

	printf ("\nINDEX [%d]:\n", (int)index_entries->length);
	for (i = 0; i < index_entries->length; i++) {
		index_entry = index_entries->contents[i];

		printf("%o ", index_entry->mode);
		printf("%s ", git_oid_allocfmt(&index_entry->oid));
		printf("%d ", git_index_entry_stage(index_entry));
		printf("%s ", index_entry->path);
		printf("\n");
	}
	printf("\n");
}
