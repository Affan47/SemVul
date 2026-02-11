add_modules_to_gui(gpointer data, gpointer user_data)
{
    ShellTree *shelltree = (ShellTree *) user_data;
    ShellModule *module = (ShellModule *) data;
    GtkTreeStore *store = GTK_TREE_STORE(shelltree->model);
    GtkTreeIter parent;

    if (!module) {
        return;
    }

    gtk_tree_store_append(store, &parent, NULL);
    gtk_tree_store_set(store, &parent, TREE_COL_NAME, module->name,
		       TREE_COL_DATA, NULL, TREE_COL_SEL, FALSE, -1);

    if (module->icon) {
	gtk_tree_store_set(store, &parent, TREE_COL_PBUF, module->icon,
			   -1);
    }

    add_module_to_menu(module->name, module->icon);

    if (module->entries) {
	ShellModuleEntry *entry;
	GSList *p;

	for (p = module->entries; p; p = g_slist_next(p)) {
	    GtkTreeIter child;
	    entry = (ShellModuleEntry *) p->data;

	    gtk_tree_store_append(store, &child, &parent);
	    gtk_tree_store_set(store, &child, TREE_COL_NAME, entry->name,
			       TREE_COL_DATA, entry,
			       TREE_COL_SEL, FALSE, -1);

	    if (entry->icon) {
		gtk_tree_store_set(store, &child, TREE_COL_PBUF,
				   entry->icon, -1);
	    }

	    add_module_entry_to_view_menu(module->name, entry->name,
					  entry->icon,
					  gtk_tree_iter_copy(&child));

	    shell_status_pulse();
	}

    }
}
