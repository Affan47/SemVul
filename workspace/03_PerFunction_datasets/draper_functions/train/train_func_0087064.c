mnt_context_get_table(struct libmnt_context *cxt,
			  const char *filename, struct libmnt_table **tb)
{
	struct libmnt_cache *cache;
	int rc;

	if (!cxt || !tb)
		return -EINVAL;

	*tb = mnt_new_table();
	if (!*tb)
		return -ENOMEM;

	if (cxt->table_errcb)
		mnt_table_set_parser_errcb(*tb, cxt->table_errcb);

	rc = mnt_table_parse_file(*tb, filename);
	if (rc) {
		mnt_free_table(*tb);
		return rc;
	}

	cache = mnt_context_get_cache(cxt);
	if (cache)
		mnt_table_set_cache(*tb, cache);

	return 0;
}
