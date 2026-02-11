gitg_hash_sha1_to_hash_new (gchar const *sha1)
{
	gchar *ret = g_new (gchar, GITG_HASH_BINARY_SIZE);
	gitg_hash_sha1_to_hash (sha1, ret);

	return ret;
}
