lt_grandfathered_db_lookup(lt_grandfathered_db_t *grandfathereddb,
			   const char            *tag)
{
	lt_grandfathered_t *retval;
	char *s;

	lt_return_val_if_fail (grandfathereddb != NULL, NULL);
	lt_return_val_if_fail (tag != NULL, NULL);

	s = strdup(tag);
	retval = lt_trie_lookup(grandfathereddb->grandfathered_entries,
				lt_strlower(s));
	free(s);
	if (retval)
		return lt_grandfathered_ref(retval);

	return NULL;
}
