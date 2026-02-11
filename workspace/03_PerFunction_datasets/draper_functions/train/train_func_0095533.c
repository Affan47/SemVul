interpret_target(struct walker *walker, char *target, unsigned char *sha1)
{
	if (!get_sha1_hex(target, sha1))
		return 0;
	if (!check_ref_format(target)) {
		struct ref *ref = alloc_ref(target);
		if (!walker->fetch_ref(walker, ref)) {
			hashcpy(sha1, ref->old_sha1);
			free(ref);
			return 0;
		}
		free(ref);
	}
	return -1;
}
