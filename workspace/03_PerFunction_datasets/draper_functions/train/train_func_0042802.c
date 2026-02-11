scan_one_pack(void *state, char *name)
{
	struct scanned_pack **ret = state, *r;
	char *s = strrchr(name, '/'), *d;

	if (git__prefixcmp(s + 1, "pack-")
	 || git__suffixcmp(s, ".pack")
	 || strlen(s + 1) != GIT_PACK_NAME_MAX + 4)
		return 0;

	d = strrchr(s + 1, '.');
	strcpy(d + 1, "idx");
	if (gitfo_exists(name))
		return 0;

	if ((r = git__malloc(sizeof(*r))) == NULL)
		return GIT_ERROR;

	*d = '\0';
	if ((r->pack = alloc_pack(s + 1)) == NULL) {
		free(r);
		return GIT_ERROR;
	}

	r->next = *ret;
	*ret = r;
	return 0;
}
