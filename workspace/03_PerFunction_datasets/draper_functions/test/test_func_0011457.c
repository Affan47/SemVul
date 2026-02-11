stack_iter_show_entry(GtkTreeIter *iter, EntryData *ed)
{
	char *func;

	gtk_tree_model_get(model, iter, STACK_FUNC, &func, -1);

	if (func && !strcmp(func, ed->func))
	{
		gtk_list_store_set(store, iter, STACK_ENTRY, ed->entry, -1);
		ed->count++;
	}
	g_free(func);
}
