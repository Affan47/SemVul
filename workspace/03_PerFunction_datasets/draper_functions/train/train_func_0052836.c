sacctmgr_list_association(int argc, char *argv[])
{
	int rc = SLURM_SUCCESS;
	slurmdb_association_cond_t *assoc_cond =
		xmalloc(sizeof(slurmdb_association_cond_t));
	List assoc_list = NULL;
	slurmdb_association_rec_t *assoc = NULL;
	int i=0;
	ListIterator itr = NULL;
	ListIterator itr2 = NULL;
	char *last_cluster = NULL;
	List tree_list = NULL;

	int field_count = 0;

	print_field_t *field = NULL;

	List format_list = list_create(slurm_destroy_char);
	List print_fields_list;

	for (i=0; i<argc; i++) {
		int command_len = strlen(argv[i]);
		if (!strncasecmp(argv[i], "Where", MAX(command_len, 5))
		    || !strncasecmp(argv[i], "Set", MAX(command_len, 3)))
			i++;
		_set_cond(&i, argc, argv, assoc_cond, format_list);
	}

	if (exit_code) {
		slurmdb_destroy_association_cond(assoc_cond);
		list_destroy(format_list);
		return SLURM_ERROR;
	} else if (!list_count(format_list)) {
		slurm_addto_char_list(format_list, "Cluster,Account,User,Part");
		if (!assoc_cond->without_parent_limits)
			slurm_addto_char_list(format_list,
					      "Share,GrpJ,GrpN,GrpCPUs,GrpMEM,"
					      "GrpS,GrpWall,GrpCPUMins,MaxJ,"
					      "MaxN,MaxCPUs,MaxS,MaxW,"
					      "MaxCPUMins,QOS,DefaultQOS");
	}
	print_fields_list = sacctmgr_process_format_list(format_list);
	list_destroy(format_list);

	if (exit_code) {
		slurmdb_destroy_association_cond(assoc_cond);
		list_destroy(print_fields_list);
		return SLURM_ERROR;
	}

	assoc_list = acct_storage_g_get_associations(db_conn, my_uid,
						     assoc_cond);
	slurmdb_destroy_association_cond(assoc_cond);

	if (!assoc_list) {
		exit_code=1;
		fprintf(stderr, " Error with request: %s\n",
			slurm_strerror(errno));
		list_destroy(print_fields_list);
		return SLURM_ERROR;
	}

	slurmdb_sort_hierarchical_assoc_list(assoc_list);

	itr = list_iterator_create(assoc_list);
	itr2 = list_iterator_create(print_fields_list);
	print_fields_header(print_fields_list);

	field_count = list_count(print_fields_list);

	while((assoc = list_next(itr))) {
		int curr_inx = 1;
		if (!last_cluster || strcmp(last_cluster, assoc->cluster)) {
			if (tree_list) {
				list_flush(tree_list);
			} else {
				tree_list =
					list_create(slurmdb_destroy_print_tree);
			}
			last_cluster = assoc->cluster;
		}
		while((field = list_next(itr2))) {
			sacctmgr_print_association_rec(
				assoc, field, tree_list,
				(curr_inx == field_count));
			curr_inx++;
		}
		list_iterator_reset(itr2);
		printf("\n");
	}

	if (tree_list)
		list_destroy(tree_list);

	list_iterator_destroy(itr2);
	list_iterator_destroy(itr);
	list_destroy(assoc_list);
	list_destroy(print_fields_list);
	tree_display = 0;
	return rc;
}
