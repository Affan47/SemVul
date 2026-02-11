__sweep(struct dm_deferred_set *ds, struct list_head *head)
{
	while ((ds->sweeper != ds->current_entry) &&
	       !ds->entries[ds->sweeper].count) {
		list_splice_init(&ds->entries[ds->sweeper].work_items, head);
		ds->sweeper = ds_next(ds->sweeper);
	}

	if ((ds->sweeper == ds->current_entry) && !ds->entries[ds->sweeper].count)
		list_splice_init(&ds->entries[ds->sweeper].work_items, head);
}
