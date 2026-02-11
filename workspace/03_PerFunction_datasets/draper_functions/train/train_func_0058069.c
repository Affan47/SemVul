open_keyfiles(char **files, uint16_t filec)
{
	uint16_t i;
	ldns_rr_list *pubkeys;
	ldns_rr *k;
	FILE *kfp;

 	pubkeys = ldns_rr_list_new();

	for (i = 0; i < filec; i++) {
		if (!(kfp = fopen(files[i], "r"))) {
			fprintf(stderr, "Error opening key file %s: %s\n", files[i], strerror(errno));
			return NULL;
		}
		if (ldns_rr_new_frm_fp(&k, kfp, NULL, NULL, NULL) != LDNS_STATUS_OK) {
			fprintf(stderr, "Error parsing the key file %s: %s\n", files[i], strerror(errno));
			ldns_rr_list_deep_free(pubkeys);
			return NULL;
		}
		fclose(kfp);
		ldns_rr_list_push_rr(pubkeys, k);
	}
	return pubkeys;
}
