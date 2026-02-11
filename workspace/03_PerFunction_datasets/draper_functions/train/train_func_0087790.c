keep_entry(struct commit **it, unsigned char *sha1)
{
	struct commit *commit;

	if (is_null_sha1(sha1))
		return 1;
	commit = lookup_commit_reference_gently(sha1, 1);
	if (!commit)
		return 0;


	if (!commit_is_complete(commit))
		return 0;
	*it = commit;
	return 1;
}
