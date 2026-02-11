aging_insert(aging_table_t *ag, const void *key, void *value)
{
	bool found;
	void *ovalue;
	time_t now = tm_time();
	struct aging_value *aval;

	g_assert(ag->magic == AGING_MAGIC);

	found = hikset_lookup_extended(ag->table, key, &ovalue);
	if (found) {
		aval = ovalue;

		if (aval->key != key && ag->kvfree != NULL) {


			(*ag->kvfree)(deconstify_pointer(key), aval->value);
		}


		aval->value = value;
		aval->last_insert = now;
		aging_moveto_tail(ag, aval);
	} else {
		WALLOC(aval);
		aval->value = value;
		aval->key = deconstify_pointer(key);
		aval->last_insert = now;
		hikset_insert(ag->table, aval);
		elist_append(&ag->list, aval);
	}
}
