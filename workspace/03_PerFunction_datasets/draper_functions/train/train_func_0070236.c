__bamc_compress_ibulk_del(dbc, key, flags)
	DBC *dbc;
	DBT *key;
	u_int32_t flags;
{
	int ret;
	BTREE_COMPRESS_STREAM stream;

	switch (flags) {
	case 0:
		__bam_cs_create_single_keyonly(&stream, key);
		return (__bamc_compress_merge_delete_dups(dbc, &stream, NULL));
	case DB_MULTIPLE:
		if ((ret = __bam_compress_check_sort_multiple_keyonly(
		    dbc->dbp, key)) != 0)
			return (ret);
		__bam_cs_create_multiple_keyonly(&stream, key);
		return (__bamc_compress_merge_delete_dups(
		    dbc, &stream, &key->doff));
	case DB_MULTIPLE_KEY:
		if ((ret = __bam_compress_check_sort_multiple_key(
		    dbc->dbp, key)) != 0)
			return (ret);
		__bam_cs_create_multiple_key(&stream, key);
		return (__bamc_compress_merge_delete(dbc, &stream, &key->doff));
	default:
		break;
	}

	return (__db_unknown_flag(
	    dbc->env, "__bamc_compress_ibulk_del", flags));
}
