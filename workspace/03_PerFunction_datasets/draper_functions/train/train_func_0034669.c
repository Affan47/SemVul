done()
{
	ht_format_group::done();

	ht_ne_shared_data *ne_shared = (ht_ne_shared_data*)shared_data;

	if (ne_shared->segments.segments) {
		free(ne_shared->segments.segments);
	}

	if (ne_shared->modnames) {
		for (uint i=0; i<ne_shared->modnames_count; i++) {
			free(ne_shared->modnames[i]);
		}
		free(ne_shared->modnames);
	}

	delete ne_shared->entrypoints;
	delete ne_shared->imports;

	free(shared_data);
}
