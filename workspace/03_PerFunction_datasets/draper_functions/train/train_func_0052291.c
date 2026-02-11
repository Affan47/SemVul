pack_refs(unsigned int flags)
{
	int fd;
	struct pack_refs_cb_data cbdata;

	memset(&cbdata, 0, sizeof(cbdata));
	cbdata.flags = flags;

	fd = hold_lock_file_for_update(&packed, git_path("packed-refs"),
				       LOCK_DIE_ON_ERROR);
	cbdata.refs_file = fdopen(fd, "w");
	if (!cbdata.refs_file)
		die("unable to create ref-pack file structure (%s)",
		    strerror(errno));


	fprintf(cbdata.refs_file, "# pack-refs with: peeled \n");

	for_each_ref(handle_one_ref, &cbdata);
	if (ferror(cbdata.refs_file))
		die("failed to write ref-pack file");
	if (fflush(cbdata.refs_file) || fsync(fd) || fclose(cbdata.refs_file))
		die("failed to write ref-pack file (%s)", strerror(errno));


	packed.fd = -1;
	if (commit_lock_file(&packed) < 0)
		die("unable to overwrite old ref-pack file (%s)", strerror(errno));
	if (cbdata.flags & PACK_REFS_PRUNE)
		prune_refs(cbdata.ref_to_prune);
	return 0;
}
