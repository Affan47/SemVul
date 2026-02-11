_process_au(List assoc_list, slurmdb_association_rec_t *assoc)
{
	slurmdb_report_assoc_rec_t *slurmdb_report_assoc =
		xmalloc(sizeof(slurmdb_report_assoc_rec_t));
	ListIterator itr = NULL;
	slurmdb_accounting_rec_t *accting = NULL;

	list_append(assoc_list, slurmdb_report_assoc);

	slurmdb_report_assoc->acct = xstrdup(assoc->acct);
	slurmdb_report_assoc->cluster = xstrdup(assoc->cluster);
	slurmdb_report_assoc->parent_acct = xstrdup(assoc->parent_acct);
	slurmdb_report_assoc->user = xstrdup(assoc->user);


	itr = list_iterator_create(assoc->accounting_list);
	while((accting = list_next(itr))) {
		slurmdb_report_assoc->cpu_secs +=
			(uint64_t)accting->alloc_secs;
		slurmdb_report_assoc->consumed_energy +=
			(uint64_t)accting->consumed_energy;
	}
	list_iterator_destroy(itr);

}
