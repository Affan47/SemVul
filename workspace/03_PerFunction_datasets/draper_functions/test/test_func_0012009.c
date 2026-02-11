text_index_rename (CamelIndex *idx,
                   const gchar *path)
{
	CamelTextIndexPrivate *p = CAMEL_TEXT_INDEX_GET_PRIVATE (idx);
	gchar *newlink, *newblock;
	gsize newlink_len, newblock_len;
	gint err, ret;

	CAMEL_TEXT_INDEX_LOCK (idx, lock);

	newblock_len = strlen (path) + 8;
	newblock = alloca (newblock_len);
	g_snprintf (newblock, newblock_len, "%s.index", path);
	ret = camel_block_file_rename (p->blocks, newblock);
	if (ret == -1) {
		CAMEL_TEXT_INDEX_UNLOCK (idx, lock);
		return -1;
	}

	newlink_len = strlen (path) + 16;
	newlink = alloca (newlink_len);
	g_snprintf (newlink, newlink_len, "%s.index.data", path);
	ret = camel_key_file_rename (p->links, newlink);
	if (ret == -1) {
		err = errno;
		camel_block_file_rename (p->blocks, idx->path);
		CAMEL_TEXT_INDEX_UNLOCK (idx, lock);
		errno = err;
		return -1;
	}

	g_free (idx->path);
	idx->path = g_strdup (newblock);

	CAMEL_TEXT_INDEX_UNLOCK (idx, lock);

	return 0;
}
