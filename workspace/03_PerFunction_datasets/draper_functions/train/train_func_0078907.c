get_one_addr (GtkTreeModel *model,
              GtkTreeIter *iter,
              int column,
              gboolean fail_if_missing,
              struct in6_addr *out)
{
	char *item = NULL;
	gboolean success = FALSE;

	gtk_tree_model_get (model, iter, column, &item, -1);
	if (!item || !strlen (item)) {
		g_free (item);
		return fail_if_missing ? FALSE : TRUE;
	}

	if (inet_pton (AF_INET6, item, out) > 0)
		success = TRUE;

	g_free (item);
	return success;
}
