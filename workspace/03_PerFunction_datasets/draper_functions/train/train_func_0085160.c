add_resource(ll_lrm_t * lrmd, char *rsc_id, int argc, int optind, char * argv[])
{
	const char * class = argv[optind];
	const char * type = argv[optind+1];
	const char * provider = argv[optind+2];
	GHashTable * params_ht = NULL;
	int tmp_ret;

	if ((argc - optind) < 3) {
		cl_log(LOG_ERR,"Not enough parameters.");
		return -2;
	}

	if (0 == strncmp(provider, "NULL", strlen("NULL"))) {
		provider=NULL;
	}


	if ((argc - optind) > 3) {
		if ( 0 > transfer_cmd_params(argc, optind+3, argv, class,
					&params_ht) ) {
			return -1;
		}
	}

	tmp_ret = lrmd->lrm_ops->add_rsc(lrmd, rsc_id, class,
						type, provider, params_ht);


	if (params_ht) {
		g_hash_table_foreach(params_ht, free_stritem_of_hashtable, NULL);
		g_hash_table_destroy(params_ht);
	}

	return (tmp_ret ? 0 : -1);
}
