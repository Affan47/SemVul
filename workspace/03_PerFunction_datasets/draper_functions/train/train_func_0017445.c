avtab_insert_nonunique(struct avtab *h, struct avtab_key *key, struct avtab_datum *datum)
{
	int hvalue;
	struct avtab_node *prev, *cur;
	u16 specified = key->specified & ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);

	if (!h || !h->htable)
		return NULL;
	hvalue = avtab_hash(key, h->mask);
	for (prev = NULL, cur = flex_array_get_ptr(h->htable, hvalue);
	     cur;
	     prev = cur, cur = cur->next) {
		if (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class == cur->key.target_class &&
		    (specified & cur->key.specified))
			break;
		if (key->source_type < cur->key.source_type)
			break;
		if (key->source_type == cur->key.source_type &&
		    key->target_type < cur->key.target_type)
			break;
		if (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class < cur->key.target_class)
			break;
	}
	return avtab_insert_node(h, hvalue, prev, cur, key, datum);
}
