patricia_traverse(patricia_t *pt,
	node_cb_t ncb, void *un, patricia_cb_t cb, void *u)
{
	patricia_check(pt);


	if (pt->root) {
		const struct patricia_node *stack[PATRICIA_MAXBITS];
		const struct patricia_node **sp = stack;
		const struct patricia_node *n = pt->root;

		while (n) {
			const struct patricia_node *z = NULL;
			const struct patricia_node *o = NULL;

			patricia_node_check(n);

			if (!n->leaf) {
				z = child_zero(n);
				o = child_one(n);
			}

			if (cb && node_has_data(n))
				(*cb)(deconstify_pointer(node_key(n)), node_keybits(n),
					deconstify_pointer(node_value(n)), u);


			if (ncb)
				(*ncb)(deconstify_pointer(n), un);

			if (z) {
				if (o) {
					g_assert(sp < &stack[PATRICIA_MAXBITS]);
					*sp++ = o;
				}
				n = z;
			} else if (o) {
				n = o;
			} else if (sp != stack) {
				n = *(--sp);
			} else {
				n = NULL;
			}
		}
	}
}
