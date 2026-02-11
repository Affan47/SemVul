hashGrow(hash_ *h)
{
	int i;
    record_ *old_recs, *new_recs;
    unsigned int old_recs_length;

	Debug("Growing Hash %p", h);

	ReturnErrIf(h->size_index == (sizes_count - 1));

    old_recs_length = sizes[h->size_index];
    old_recs = h->records;

	new_recs = calloc(sizes[++h->size_index], sizeof(record_));
	ReturnErrIf(new_recs == NULL);
	h->records = new_recs;

    h->records_count = 0;


    for (i=0; i < old_recs_length; i++) {
        if (old_recs[i].hash && old_recs[i].key) {
            ReturnErrIf(hashAdd(h, old_recs[i].key, old_recs[i].record));
		}
	}

    free(old_recs);

    return 0;
}
