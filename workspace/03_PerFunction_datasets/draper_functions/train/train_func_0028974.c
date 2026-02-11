prepare_index(int argc, const char **argv, const char *prefix)
{
	int fd;
	struct string_list partial;
	const char **pathspec = NULL;

	if (interactive) {
		interactive_add(argc, argv, prefix);
		if (read_cache() < 0)
			die("index file corrupt");
		commit_style = COMMIT_AS_IS;
		return get_index_file();
	}

	if (read_cache() < 0)
		die("index file corrupt");

	if (*argv)
		pathspec = get_pathspec(prefix, argv);


	if (all || (also && pathspec && *pathspec)) {
		int fd = hold_locked_index(&index_lock, 1);
		add_files_to_cache(also ? prefix : NULL, pathspec, 0);
		refresh_cache(REFRESH_QUIET);
		if (write_cache(fd, active_cache, active_nr) ||
		    close_lock_file(&index_lock))
			die("unable to write new_index file");
		commit_style = COMMIT_NORMAL;
		return index_lock.filename;
	}


	if (!pathspec || !*pathspec) {
		fd = hold_locked_index(&index_lock, 1);
		refresh_cache(REFRESH_QUIET);
		if (write_cache(fd, active_cache, active_nr) ||
		    commit_locked_index(&index_lock))
			die("unable to write new_index file");
		commit_style = COMMIT_AS_IS;
		return get_index_file();
	}


	commit_style = COMMIT_PARTIAL;

	if (file_exists(git_path("MERGE_HEAD")))
		die("cannot do a partial commit during a merge.");

	memset(&partial, 0, sizeof(partial));
	partial.strdup_strings = 1;
	if (list_paths(&partial, initial_commit ? NULL : "HEAD", prefix, pathspec))
		exit(1);

	discard_cache();
	if (read_cache() < 0)
		die("cannot read the index");

	fd = hold_locked_index(&index_lock, 1);
	add_remove_files(&partial);
	refresh_cache(REFRESH_QUIET);
	if (write_cache(fd, active_cache, active_nr) ||
	    close_lock_file(&index_lock))
		die("unable to write new_index file");

	fd = hold_lock_file_for_update(&false_lock,
				       git_path("next-index-%"PRIuMAX,
						(uintmax_t) getpid()),
				       LOCK_DIE_ON_ERROR);

	create_base_index();
	add_remove_files(&partial);
	refresh_cache(REFRESH_QUIET);

	if (write_cache(fd, active_cache, active_nr) ||
	    close_lock_file(&false_lock))
		die("unable to write temporary index file");

	discard_cache();
	read_cache_from(false_lock.filename);

	return false_lock.filename;
}
