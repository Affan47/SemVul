PMI_KVS_Get( const char kvsname[], const char key[], char value[], int length)
{
	int i, j, rc;

	if (pmi_debug)
		fprintf(stderr, "In: PMI_KVS_Get(%s)\n", key);

	if ((kvsname == NULL) || (strlen(kvsname) > PMI_MAX_KVSNAME_LEN))
		return PMI_ERR_INVALID_KVS;
	if ((key == NULL) || (strlen(key) >PMI_MAX_KEY_LEN))
		return PMI_ERR_INVALID_KEY;
	if (value == NULL)
		return PMI_ERR_INVALID_VAL;


	pthread_mutex_lock(&kvs_mutex);
	for (i=0; i<kvs_rec_cnt; i++) {
		if (kvs_recs[i].kvs_state == KVS_STATE_DEFUNCT)
			continue;
		if (strncmp(kvs_recs[i].kvs_name, kvsname, PMI_MAX_KVSNAME_LEN))
			continue;
		for (j=0; j<kvs_recs[i].kvs_cnt; j++) {
			if (strncmp(kvs_recs[i].kvs_keys[j], key,
				    PMI_MAX_KEY_LEN))
				continue;
			if (strlen(kvs_recs[i].kvs_values[j]) > (length-1))
				rc = PMI_ERR_INVALID_LENGTH;
			else {
				strncpy(value, kvs_recs[i].kvs_values[j],
					length);
				rc = PMI_SUCCESS;
			}
			goto fini;
		}
		rc = PMI_ERR_INVALID_KEY;
		goto fini;
	}
	rc = PMI_ERR_INVALID_KVS;

fini:	pthread_mutex_unlock(&kvs_mutex);
	return rc;
}
