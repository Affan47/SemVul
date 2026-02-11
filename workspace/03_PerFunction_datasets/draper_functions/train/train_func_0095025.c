bch_keylist_pop(struct keylist *l)
{
	struct bkey *k = l->keys;

	if (k == l->top)
		return NULL;

	while (bkey_next(k) != l->top)
		k = bkey_next(k);

	return l->top = k;
}
