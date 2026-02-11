_isdefault(List qos_list)
{
	int rc = 0;
	slurmdb_association_cond_t assoc_cond;
	slurmdb_association_rec_t *assoc = NULL;
	ListIterator itr;
	List ret_list = NULL;
	char *name = NULL;

	if (!qos_list || !list_count(qos_list))
		return rc;


	xassert(g_qos_list);

	memset(&assoc_cond, 0, sizeof(slurmdb_association_cond_t));
	assoc_cond.without_parent_info = 1;
	assoc_cond.def_qos_id_list = list_create(slurm_destroy_char);

	itr = list_iterator_create(qos_list);
	while ((name = list_next(itr))) {
		uint32_t id = str_2_slurmdb_qos(g_qos_list, name);
		if (id == NO_VAL)
			continue;
		list_append(assoc_cond.def_qos_id_list,
			    xstrdup_printf("%u", id));
	}
	list_iterator_destroy(itr);

	ret_list = acct_storage_g_get_associations(
		db_conn, my_uid, &assoc_cond);
	list_destroy(assoc_cond.def_qos_id_list);

	if (!ret_list || !list_count(ret_list))
		goto end_it;

	fprintf(stderr," Associations listed below have these "
		"as their Default QOS.\n");
	itr = list_iterator_create(ret_list);
	while((assoc = list_next(itr))) {
		name = slurmdb_qos_str(g_qos_list, assoc->def_qos_id);
		if (!assoc->user) {

			fprintf(stderr,
				"  DefQOS = %-10s C = %-10s A = %-20s\n",
				name, assoc->cluster, assoc->acct);
		} else if (assoc->partition) {

			fprintf(stderr,
				"  DefQOS = %-10s C = %-10s A = %-20s "
				"U = %-9s P = %s\n",
				name, assoc->cluster, assoc->acct,
				assoc->user, assoc->partition);
		} else {
			fprintf(stderr,
				"  DefQOS = %-10s C = %-10s A = %-20s "
				"U = %-9s\n",
				name, assoc->cluster, assoc->acct, assoc->user);
		}
	}
	list_iterator_destroy(itr);
	rc = 1;
end_it:
	if (ret_list)
		list_destroy(ret_list);

	return rc;
}
