erbtree_getnode(const erbtree_t *tree, const void *key)
{
	rbnode_t *parent;
	bool is_left;

	erbtree_check(tree);
	g_assert(key != NULL);

	if (erbtree_is_extended(tree)) {
		return do_lookup_ext(ERBTREE_E(tree), key, &parent, &is_left);
	} else {
		return do_lookup(tree, key, &parent, &is_left);
	}
}
