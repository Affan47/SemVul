upload_stats_find(const struct sha1 *sha1, const char *pathname, uint64 size)
{
	struct ul_stats *s = NULL;

	if (upload_stats_list) {
		static const struct ul_stats zero_stats;
		struct ul_stats key;
		const void *orig_key;

		g_assert(upload_stats_by_sha1);

		if (sha1) {
			s = hikset_lookup(upload_stats_by_sha1, sha1);
			if (s)
				goto done;
		}

		key = zero_stats;
		key.pathname = atom_str_get(pathname);
		key.size = size;

		if (hash_list_find(upload_stats_list, &key, &orig_key))
			s = deconstify_pointer(orig_key);
		atom_str_free_null(&key.pathname);

		if (s && sha1) {

			if (NULL == s->sha1) {


				s->sha1 = atom_sha1_get(sha1);
			} else {

				struct ul_stats *old =
					hikset_lookup(upload_stats_by_sha1, s->sha1);

				g_assert(old == s);

				hikset_remove(upload_stats_by_sha1, s->sha1);
				atom_sha1_free(s->sha1);
				s->sha1 = atom_sha1_get(sha1);
			}
			hikset_insert_key(upload_stats_by_sha1, &s->sha1);
		}
	}

done:


	g_assert(!(s && sha1) || s->sha1);


	if (s != NULL) {
		g_assert(atom_is_str(s->pathname));
		g_assert(atom_is_str(s->filename));
		g_assert(s->norm >= 0.0);
	}

	return s;
}
