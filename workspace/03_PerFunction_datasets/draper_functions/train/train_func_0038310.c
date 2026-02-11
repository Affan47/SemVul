vattr_map_insert(vattr_map_entry *vae)
{
	char *copy_of_type_name = NULL;
	PR_ASSERT(the_map);
	copy_of_type_name = slapi_ch_strdup(vae->type_name);
	if (NULL == copy_of_type_name) {
		slapd_nasty(sourcefile,6,0);
		return ENOMEM;
	}

	slapi_rwlock_wrlock(the_map->lock);


	PR_ASSERT(NULL == PL_HashTableLookupConst(the_map->hashtable,(void*)copy_of_type_name));
    PL_HashTableAdd(the_map->hashtable,(void*)copy_of_type_name,(void*)vae);

	slapi_rwlock_unlock(the_map->lock);
	return 0;
}
