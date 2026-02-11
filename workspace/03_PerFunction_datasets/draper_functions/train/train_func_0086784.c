btree_lookup(const struct btree *t, uint32_t k)
{
	uint32_t key = _shuffle(k);
	struct node *p, *const *c = _lookup(&t->root, key, &p);
	return (*c) ? (*c)->data : NULL;
}
