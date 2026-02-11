pack_entry_find_prefix(
	struct git_pack_entry *e,
	struct pack_backend *backend,
	const git_oid *short_oid,
	size_t len)
{
	int error;
	size_t i;
	git_oid found_full_oid = {{0}};
	bool found = false;
	struct git_pack_file *last_found = backend->last_found;

	if (last_found) {
		error = git_pack_entry_find(e, last_found, short_oid, len);
		if (error == GIT_EAMBIGUOUS)
			return error;
		if (!error) {
			git_oid_cpy(&found_full_oid, &e->sha1);
			found = true;
		}
	}

	for (i = 0; i < backend->packs.length; ++i) {
		struct git_pack_file *p;

		p = git_vector_get(&backend->packs, i);
		if (p == last_found)
			continue;

		error = git_pack_entry_find(e, p, short_oid, len);
		if (error == GIT_EAMBIGUOUS)
			return error;
		if (!error) {
			if (found && git_oid_cmp(&e->sha1, &found_full_oid))
				return git_odb__error_ambiguous("found multiple pack entries");
			git_oid_cpy(&found_full_oid, &e->sha1);
			found = true;
			backend->last_found = p;
		}
	}

	if (!found)
		return git_odb__error_notfound("no matching pack entry for prefix", short_oid);
	else
		return 0;
}
