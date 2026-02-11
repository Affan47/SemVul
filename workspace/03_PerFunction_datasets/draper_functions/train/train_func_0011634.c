_reset_usage(void)
{
	ListIterator itr = NULL;
	slurmdb_association_rec_t *assoc = NULL;
	slurmdb_qos_rec_t *qos = NULL;
	assoc_mgr_lock_t locks = { WRITE_LOCK, NO_LOCK,
				   WRITE_LOCK, NO_LOCK, NO_LOCK };

	if (!calc_fairshare)
		return SLURM_SUCCESS;

	assoc_mgr_lock(&locks);

	xassert(assoc_mgr_association_list);

	itr = list_iterator_create(assoc_mgr_association_list);


	while ((assoc = list_next(itr))) {
		assoc->usage->usage_raw = 0;
		assoc->usage->grp_used_wall = 0;
	}
	list_iterator_destroy(itr);

	itr = list_iterator_create(assoc_mgr_qos_list);
	while ((qos = list_next(itr))) {
		qos->usage->usage_raw = 0;
		qos->usage->grp_used_wall = 0;
	}
	list_iterator_destroy(itr);
	assoc_mgr_unlock(&locks);

	return SLURM_SUCCESS;
}
