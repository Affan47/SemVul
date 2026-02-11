grouplist_expand_upwards(GtkCMCTree *ctree, const gchar *name) {
	const gchar *ptr;
	gchar *newname=g_malloc0(strlen(name));

	for (ptr=name; *ptr; ptr++) {
		if (*ptr == '.')
			gtk_cmctree_expand(ctree,
				grouplist_hash_get_branch_node(newname));
		newname[ptr-name] = *ptr;
	}
	g_free(newname);
}
