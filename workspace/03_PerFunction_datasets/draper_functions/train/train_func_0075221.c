build_fake_ancestor(struct patch *list, const char *filename)
{
	struct patch *patch;
	struct index_state result = { 0 };
	int fd;


	for (patch = list; patch; patch = patch->next) {
		const unsigned char *sha1_ptr;
		unsigned char sha1[20];
		struct cache_entry *ce;
		const char *name;

		name = patch->old_name ? patch->old_name : patch->new_name;
		if (0 < patch->is_new)
			continue;
		else if (get_sha1(patch->old_sha1_prefix, sha1))

			if (!patch->lines_added && !patch->lines_deleted) {
				if (get_current_sha1(patch->new_name, sha1) ||
				    get_current_sha1(patch->old_name, sha1))
					die("mode change for %s, which is not "
						"in current HEAD", name);
				sha1_ptr = sha1;
			} else
				die("sha1 information is lacking or useless "
					"(%s).", name);
		else
			sha1_ptr = sha1;

		ce = make_cache_entry(patch->old_mode, sha1_ptr, name, 0, 0);
		if (add_index_entry(&result, ce, ADD_CACHE_OK_TO_ADD))
			die ("Could not add %s to temporary index", name);
	}

	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0 || write_index(&result, fd) || close(fd))
		die ("Could not write temporary index to %s", filename);

	discard_index(&result);
}
