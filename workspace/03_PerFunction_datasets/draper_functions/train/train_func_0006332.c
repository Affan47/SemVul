custom_editor_cb (GtkWidget *widget, gpointer user_data)
{
	VgDefaultView *view = user_data;
	GtkTreeSelection *selection;
	VgErrorStack *stack = NULL;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *path, *var;
	GString *new;
	char **argv;
	int argc;
	int i;

	selection = gtk_tree_view_get_selection ((GtkTreeView *) view->table);
	if (!gtk_tree_selection_get_selected (selection, &model, &iter))
		return;

	gtk_tree_model_get (model, &iter, COL_POINTER_STACK, &stack, -1);
	if (stack == NULL)
		return;

	if (!(path = resolve_full_path ((VgToolView *) view, stack)))
		return;

	if (!(var = gconf_client_get_string (view->gconf, CUSTOM_EDITOR_KEY, NULL))) {
		g_free (path);
		return;
	}

	if (!g_shell_parse_argv (var, &argc, &argv, NULL)) {
		g_free (path);
		g_free (var);
		return;
	}

	g_free (var);

	for (i = 0; i < argc; i++) {
		if ((var = strstr (argv[i], "${")) != NULL && (var > argv[i] ? var[-1] != '\\' : TRUE)) {
			new = g_string_new ("");
			g_string_append_len (new, argv[i], var - argv[i]);

			if (!strncasecmp (var, "${filename}", 11)) {
				g_string_append (new, path);
				var += 11;
			} else if (!strncasecmp (var, "${lineno}", 9)) {
				g_string_append_printf (new, "%u", stack->info.src.lineno);
				var += 9;
			} else {
				g_warning ("Invalid editor variable: %s", var);
			}

			g_string_append (new, var);

			g_free (argv[i]);
			argv[i] = new->str;
			g_string_free (new, FALSE);
		}
	}

	g_free (path);

	g_spawn_async (NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);

	for (i = 0; i < argc; i++)
		g_free (argv[i]);
	g_free (argv);
}
