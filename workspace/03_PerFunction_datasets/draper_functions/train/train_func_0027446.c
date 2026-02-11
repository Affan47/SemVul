xmlnode_find_child(xmlnode_t *n, const char *name) {
	if (!n || !n->children)
		return NULL;

	for (n = n->children; n; n = n->next)
		if (!xstrcmp(n->name, name))
			return n;
	return NULL;
}
