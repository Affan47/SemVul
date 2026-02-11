camel_uid_cache_save_uid (CamelUIDCache *cache,
                          const gchar *uid)
{
	struct _uid_state *state;
	gpointer old_uid;

	g_return_if_fail (uid != NULL);

	if (g_hash_table_lookup_extended (cache->uids, uid, (gpointer *) &old_uid, (gpointer *) &state)) {
		state->save = TRUE;
		state->level = cache->level;
	} else {
		state = g_new (struct _uid_state, 1);
		state->save = TRUE;
		state->level = cache->level;

		g_hash_table_insert (cache->uids, g_strdup (uid), state);
	}
}
