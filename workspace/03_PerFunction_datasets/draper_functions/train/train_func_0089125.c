server_list_prepend_download(struct dl_server *server, enum dl_list idx,
	struct download *d)
{
	g_assert(dl_server_valid(server));
	download_check(d);

	server_sha1_count_inc(server, d);
	list_prepend(server_list_by_index(server, idx), d);
}
