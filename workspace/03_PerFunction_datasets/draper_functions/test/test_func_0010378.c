pagetypeinfo_showblockcount(struct seq_file *m, void *arg)
{
	int mtype;
	pg_data_t *pgdat = (pg_data_t *)arg;

	seq_printf(m, "\n%-23s", "Number of blocks type ");
	for (mtype = 0; mtype < MIGRATE_TYPES; mtype++)
		seq_printf(m, "%12s ", migratetype_names[mtype]);
	seq_putc(m, '\n');
	walk_zones_in_node(m, pgdat, pagetypeinfo_showblockcount_print);

	return 0;
}
