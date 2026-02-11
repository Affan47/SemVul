ast_hashtab_remove_object_via_lookup_nolock(struct ast_hashtab *tab, void *obj)
{

	unsigned int h;
	struct ast_hashtab_bucket *b;

	if (!tab || !obj)
		return 0;

	h = (*tab->hash)(obj) % tab->hash_tab_size;
	for (b = tab->array[h]; b; b = b->next) {

		if (!(*tab->compare)(obj, b->object)) {
			const void *obj2;

			obj2 = ast_hashtab_remove_object_internal(tab, b, h);

			return (void *) obj2;
		}
	}

	return 0;
}
