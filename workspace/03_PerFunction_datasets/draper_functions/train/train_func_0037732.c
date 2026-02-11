PMI_KVS_Iter_next(const char kvsname[], char key[], int key_len,
		char val[], int val_len)
{
	int i, rc;

	if (pmi_debug)
		fprintf(stderr, "In: PMI_KVS_Iter_next\n");

	if ((kvsname == NULL) || (strlen(kvsname) > PMI_MAX_KVSNAME_LEN))
		return PMI_ERR_INVALID_KVS;
	if (key == NULL)
		return PMI_ERR_INVALID_KEY;
	if (val == NULL)
		return PMI_ERR_INVALID_VAL;


	pthread_mutex_lock(&kvs_mutex);
	for (i=0; i<kvs_rec_cnt; i++) {
		if (kvs_recs[i].kvs_state == KVS_STATE_DEFUNCT)
			continue;
		if (strncmp(kvs_recs[i].kvs_name, kvsname, PMI_MAX_KVSNAME_LEN))
			continue;
		kvs_recs[i].kvs_inx++;
		if (kvs_recs[i].kvs_inx >= kvs_recs[i].kvs_cnt) {
			key[0] = '\0';
			val[0] = '\0';
			rc = PMI_SUCCESS;
		} else if (strlen(kvs_recs[i].kvs_keys[kvs_recs[i].kvs_inx]) >
				(key_len-1)) {
			rc = PMI_ERR_INVALID_KEY_LENGTH;
		} else if (strlen(kvs_recs[i].kvs_values[kvs_recs[i].kvs_inx]) >
				(val_len-1)) {
			rc = PMI_ERR_INVALID_VAL_LENGTH;
		} else {
			strncpy(key, kvs_recs[i].kvs_keys[kvs_recs[i].kvs_inx],
				key_len);
			strncpy(val,
				kvs_recs[i].kvs_values[kvs_recs[i].kvs_inx],
				val_len);
			rc = PMI_SUCCESS;
		}
		goto fini;
	}
	rc = PMI_ERR_INVALID_KVS;

fini:	pthread_mutex_unlock(&kvs_mutex);
	return rc;
}
