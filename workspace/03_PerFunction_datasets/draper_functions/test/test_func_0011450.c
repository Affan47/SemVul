transfer_cmd_params(int amount, int start, char * argv[], const char * class,
GHashTable ** params_ht)
{
	int i, len_tmp;
	char * delimit, * key, * value;
	char buffer[21];

	if (amount < start) {
		return -1;
	}

	if ( strncmp("ocf", class, strlen("ocf"))==0
	    || strncmp("stonith", class, strlen("stonith"))==0) {
		*params_ht = g_hash_table_new(g_str_hash, g_str_equal);

		for (i=start; i<amount; i++) {
			delimit = strchr(argv[i], '=');
			if (!delimit) {
				cl_log(LOG_ERR, "Parameter %s is invalid for "
					"the OCF standard.", argv[i]);
				goto error_return;
			}

			len_tmp = strnlen(delimit+1, MAX_PARAM_LEN) + 1;
			value = g_new(gchar, len_tmp);
			strncpy(value, delimit+1, len_tmp);

			len_tmp = strnlen(argv[i], MAX_PARAM_LEN) - strnlen(delimit, MAX_PARAM_LEN);
			key = g_new(gchar, len_tmp+1);
			key[len_tmp] = '\0';
			strncpy(key, argv[i], len_tmp);

			g_hash_table_insert(*params_ht, key, value);
		}
	} else if ( strncmp("lsb", class, strlen("lsb")) == 0
		   || strncmp("heartbeat", class, strlen("heartbeat")) == 0 ) {


		*params_ht = g_hash_table_new(g_str_hash, g_str_equal);

		memset(buffer, '0', 21);
		for (i=start; i<amount; i++) {
			snprintf(buffer, 20, "%d", i-start+1);
			g_hash_table_insert( *params_ht, g_strdup(buffer),
						g_strdup(argv[i]));

		}
	} else {
		fprintf(stderr, "Not supported resource agent class.\n");
		return -1;
	}

	return 0;

error_return:
	if (*params_ht) {
		g_hash_table_foreach(*params_ht, free_stritem_of_hashtable, NULL);
		g_hash_table_destroy(*params_ht);
		*params_ht = NULL;
	}
	return -1;
}
