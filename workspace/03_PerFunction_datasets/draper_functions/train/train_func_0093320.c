xmms_magic_add_node (GNode *tree, const gchar *s, GNode *prev_node)
{
	xmms_magic_entry_t *entry;
	gpointer *data = tree->data;
	guint indent = 0, prev_indent;

	g_assert (s);

	XMMS_DBG ("adding magic spec to tree '%s'", (gchar *) data[0]);


	while (*s == '>') {
		indent++;
		s++;
	}

	entry = parse_entry (s);
	if (!entry) {
		XMMS_DBG ("cannot parse magic entry");
		return NULL;
	}

	if (!indent) {
		return g_node_append_data (tree, entry);
	}

	if (!prev_node) {
		XMMS_DBG ("invalid indent level");
		xmms_magic_entry_free (entry);
		return NULL;
	}

	prev_indent = g_node_depth (prev_node) - 2;

	if (indent > prev_indent) {

		if (indent != prev_indent + 1) {
			XMMS_DBG ("invalid indent level");
			xmms_magic_entry_free (entry);
			return NULL;
		}

		return g_node_append_data (prev_node, entry);
	} else {
		while (indent < prev_indent) {
			prev_indent--;
			prev_node = prev_node->parent;
		}

		return g_node_insert_after (prev_node->parent, prev_node,
		                            g_node_new (entry));
	}
}
