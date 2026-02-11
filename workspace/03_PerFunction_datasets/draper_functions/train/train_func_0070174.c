e2_option_tree_row_write_to_string (E2_OptionSet *set,
	GtkTreeIter *iter, gint level)
{
	GString *treerow = g_string_sized_new (128);
	gint j;
	for (j = 0; j < level; j++)
		treerow = g_string_append_c (treerow, '\t');
	GList *column;
	j = 0;
	for (column = set->ex.tree.columns; column != NULL; column = g_list_next (column))
	{
		E2_OptionTreeColumn *opt = column->data;
		switch (opt->type)
		{
			case E2_OPTION_TREE_TYPE_BOOL:
			{
				gboolean int_data;
				gtk_tree_model_get (set->ex.tree.model, iter, j, &int_data, -1);
				if (int_data)
					treerow = g_string_append (treerow, "true");
				else
					treerow = g_string_append (treerow, "false");
			}
			break;
			case E2_OPTION_TREE_TYPE_STR:
			case E2_OPTION_TREE_TYPE_ICON:
			case E2_OPTION_TREE_TYPE_SEL:
			case E2_OPTION_TREE_TYPE_KEY:
			{
				gchar *str_data;
				gtk_tree_model_get (set->ex.tree.model, iter,  j, &str_data, -1);

				if (str_data != NULL)
				{
					if (j == 0 && str_data[0] == '>')
						treerow = g_string_append (treerow, "\\");
					if ((str_data[0] != '\0') && ((strchr (str_data, '|')) != NULL))
					{
						gchar **split = g_strsplit (str_data, "|", -1);
						g_free (str_data);
						str_data = g_strjoinv ("\\|", split);
						g_strfreev (split);
					}
					treerow = g_string_append (treerow, str_data);
					g_free (str_data);
				}
			}
			break;
			default:
			break;
		}
		treerow = g_string_append_c (treerow, '|');
		j++;
	}

	treerow = g_string_truncate (treerow, treerow->len -1);

	gchar *result = g_string_free (treerow, FALSE);
	return result;
}
