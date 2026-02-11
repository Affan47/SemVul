acl_ht_remove_and_free(acl_ht_t * acl_ht,
					PLHashNumber key){
	char *old_value = NULL;

	if ( (old_value = (char *)acl_ht_lookup( acl_ht, key)) != NULL ) {
		acl_ht_remove( acl_ht, key);
		slapi_ch_free_string(&old_value);
	}
}
