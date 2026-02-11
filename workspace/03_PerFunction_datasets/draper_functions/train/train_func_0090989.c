stktable_lookup_key(struct stktable *t, struct stktable_key *key)
{
	struct ebmb_node *eb;

	if (t->type == STKTABLE_TYPE_STRING)
		eb = ebst_lookup_len(&t->keys, key->key, key->key_len+1 < t->key_size ? key->key_len : t->key_size-1);
	else
		eb = ebmb_lookup(&t->keys, key->key, t->key_size);

	if (unlikely(!eb)) {

		return NULL;
	}

	return ebmb_entry(eb, struct stksess, key);
}
