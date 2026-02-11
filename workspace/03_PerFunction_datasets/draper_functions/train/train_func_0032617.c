read_idx_option(struct pack_idx_option *opts, const char *pack_name)
{
	struct packed_git *p = add_packed_git(pack_name, strlen(pack_name), 1);

	if (!p)
		die("Cannot open existing pack file '%s'", pack_name);
	if (open_pack_index(p))
		die("Cannot open existing pack idx file for '%s'", pack_name);


	opts->version = p->index_version;

	if (opts->version == 2)
		read_v2_anomalous_offsets(p, opts);


	close_pack_index(p);
	free(p);
}
