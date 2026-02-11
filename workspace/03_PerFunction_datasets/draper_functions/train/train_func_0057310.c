cob_table_sort_init (const int nkeys, const unsigned char *collating_sequence)
{
	sort_nkeys = 0;
	sort_keys = cob_malloc (nkeys * sizeof (struct cob_file_key));
	if (collating_sequence) {
		sort_collate = collating_sequence;
	} else {
		sort_collate = cob_current_module->collating_sequence;
	}
}
