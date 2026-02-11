attach_process_review (AttachProcess *ap)
{
	gchar *ps_output, *begin, *end;
	guint line_num = 0;
	GtkTreeStore *store;

	g_return_if_fail (ap);
	g_return_if_fail (ap->ps_output);
	store = GTK_TREE_STORE (gtk_tree_view_get_model
							(GTK_TREE_VIEW (ap->treeview)));
	g_return_if_fail (store);

	ps_output = g_strdup (ap->ps_output);
	end = ps_output;
	while (*end)
	{
		begin = end;
		while (*end && *end != '\n') end++;
		if (++line_num > 2)
		{
			*end = '\0';
			attach_process_add_line (ap, store, begin);
		}
		end++;
	}
	g_free (ps_output);

	iter_stack_clear (ap);
	gtk_tree_view_expand_all (GTK_TREE_VIEW (ap->treeview));
}
