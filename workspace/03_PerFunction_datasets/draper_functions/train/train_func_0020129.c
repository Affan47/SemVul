ce_compare_gitlink(struct cache_entry *ce)
{
	unsigned char sha1[20];


	if (resolve_gitlink_ref(ce->name, "HEAD", sha1) < 0)
		return 0;
	return hashcmp(sha1, ce->sha1);
}
