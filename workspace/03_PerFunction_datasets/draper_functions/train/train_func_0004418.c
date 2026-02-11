kb_init(void)
{
	GtkTreeIter parent, iter;
	gsize g, i;
	gchar *label;
	GeanyKeyGroup *group;
	GeanyKeyBinding *kb;

	if (store == NULL)
		kb_init_tree();

	foreach_ptr_array(group, g, keybinding_groups)
	{
		gtk_tree_store_append(store, &parent, NULL);
		gtk_tree_store_set(store, &parent, KB_TREE_ACTION, group->label,
			KB_TREE_INDEX, g, -1);

		foreach_ptr_array(kb, i, group->key_items)
		{
			label = keybindings_get_label(kb);
			gtk_tree_store_append(store, &iter, &parent);
			gtk_tree_store_set(store, &iter, KB_TREE_ACTION, label,
				KB_TREE_EDITABLE, TRUE, KB_TREE_INDEX, kb->id, -1);
			kb_set_shortcut(store, &iter, kb->key, kb->mods);
			g_free(label);
		}
	}
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree));
}
