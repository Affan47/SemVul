sacctmgr_delete_cluster(int argc, char *argv[])
{
	int rc = SLURM_SUCCESS;
	slurmdb_cluster_cond_t *cluster_cond =
		xmalloc(sizeof(slurmdb_cluster_cond_t));
	int i=0;
	List ret_list = NULL;
	int cond_set = 0, prev_set;

	slurmdb_init_cluster_cond(cluster_cond, 0);
	cluster_cond->cluster_list = list_create(slurm_destroy_char);

	for (i=0; i<argc; i++) {
		int command_len = strlen(argv[i]);
		if (!strncasecmp(argv[i], "Where", MAX(command_len, 5))
		    || !strncasecmp(argv[i], "Set", MAX(command_len, 3)))
			i++;
		prev_set = _set_cond(&i, argc, argv, cluster_cond, NULL);
		cond_set |= prev_set;
	}

	if (exit_code) {
		slurmdb_destroy_cluster_cond(cluster_cond);
		return SLURM_ERROR;
	} else if (!cond_set) {
		exit_code=1;
		fprintf(stderr,
			" No conditions given to remove, not executing.\n");
		slurmdb_destroy_cluster_cond(cluster_cond);
		return SLURM_ERROR;
	}

	if (!list_count(cluster_cond->cluster_list)
	   && !cluster_cond->classification) {
		exit_code=1;
		fprintf(stderr,
			"problem with delete request.  "
			"Nothing given to delete.\n");
		slurmdb_destroy_cluster_cond(cluster_cond);
		return SLURM_SUCCESS;
	}
	notice_thread_init();
	ret_list = acct_storage_g_remove_clusters(
		db_conn, my_uid, cluster_cond);
	rc = errno;
	notice_thread_fini();

	slurmdb_destroy_cluster_cond(cluster_cond);

	if (ret_list && list_count(ret_list)) {
		char *object = NULL;
		ListIterator itr = list_iterator_create(ret_list);


		if (rc == ESLURM_JOBS_RUNNING_ON_ASSOC) {
			fprintf(stderr, " Error with request: %s\n",
				slurm_strerror(rc));
			while((object = list_next(itr))) {
				fprintf(stderr,"  %s\n", object);
			}
			list_destroy(ret_list);
			acct_storage_g_commit(db_conn, 0);
			return rc;
		}
		printf(" Deleting clusters...\n");
		while((object = list_next(itr))) {
			printf("  %s\n", object);
		}
		list_iterator_destroy(itr);
		if (commit_check("Would you like to commit changes?")) {
			acct_storage_g_commit(db_conn, 1);
		} else {
			printf(" Changes Discarded\n");
			acct_storage_g_commit(db_conn, 0);
		}
	} else if (ret_list) {
		printf(" Nothing deleted\n");
		rc = SLURM_ERROR;
	} else {
		exit_code=1;
		fprintf(stderr, " Error with request: %s\n",
			slurm_strerror(errno));
		rc = SLURM_ERROR;
	}

	if (ret_list)
		list_destroy(ret_list);

	return rc;
}
