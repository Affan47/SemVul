upload_stats_enforce_local_filename(const shared_file_t *sf)
{
	struct ul_stats *s;
	const struct sha1 *sha1;
	const char *name;

	if (!upload_stats_by_sha1)
		return;

	sha1 = sha1_hash_available(sf) ? shared_file_sha1(sf) : NULL;

	if (!sha1)
		return;

	s = hikset_lookup(upload_stats_by_sha1, sha1);

	if (NULL == s)
		return;

	name = shared_file_name_nfc(sf);
	if (name == s->filename)
		return;


	hash_list_remove(upload_stats_list, s);
	atom_str_change(&s->pathname, shared_file_path(sf));
	atom_str_change(&s->filename, name);
	hash_list_append(upload_stats_list, s);

	gcu_upload_stats_gui_update_name(s);
}
