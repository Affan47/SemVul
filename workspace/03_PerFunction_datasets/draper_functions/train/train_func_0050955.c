do_fetch_pack(int fd[2],
		const struct ref *orig_ref,
		int nr_match,
		char **match,
		char **pack_lockfile)
{
	struct ref *ref = copy_ref_list(orig_ref);
	unsigned char sha1[20];

	if (is_repository_shallow() && !server_supports("shallow"))
		die("Server does not support shallow clients");
	if (server_supports("multi_ack")) {
		if (args.verbose)
			fprintf(stderr, "Server supports multi_ack\n");
		multi_ack = 1;
	}
	if (server_supports("side-band-64k")) {
		if (args.verbose)
			fprintf(stderr, "Server supports side-band-64k\n");
		use_sideband = 2;
	}
	else if (server_supports("side-band")) {
		if (args.verbose)
			fprintf(stderr, "Server supports side-band\n");
		use_sideband = 1;
	}
	if (everything_local(&ref, nr_match, match)) {
		packet_flush(fd[1]);
		goto all_done;
	}
	if (find_common(fd, sha1, ref) < 0)
		if (!args.keep_pack)


			fprintf(stderr, "warning: no common commits\n");

	if (get_pack(fd, pack_lockfile))
		die("git fetch-pack: fetch failed.");

 all_done:
	return ref;
}
