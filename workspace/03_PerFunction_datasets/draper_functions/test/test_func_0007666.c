_hdb_set_master_key_usage(krb5_context context, HDB *db, unsigned int key_usage)
{
    if (db->hdb_master_key_set == 0)
	return HDB_ERR_NO_MKEY;
    db->hdb_master_key->key_usage = key_usage;
    return 0;
}
