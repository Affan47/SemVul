xmlnode_free(xmlnode_t *n) {
	xmlnode_t *m;

	if (!n)
		return;

	for (m = n->children; m;) {
		xmlnode_t *cur = m;
		m = m->next;
		xmlnode_free(cur);
	}

	xfree(n->name);
	string_free(n->data, 1);
	array_free(n->atts);
	xfree(n);
}
