ast_hashtab_lookup_internal(struct ast_hashtab *tab, const void *obj, unsigned int h)
{
	struct ast_hashtab_bucket *b;

	for (b = tab->array[h]; b; b = b->next) {
		if (!(*tab->compare)(obj,b->object)) {

			return (void*) b->object;
		}
	}

	return NULL;
}
