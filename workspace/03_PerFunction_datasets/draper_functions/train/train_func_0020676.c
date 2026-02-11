scheme_description_cell_data_func (GtkTreeViewColumn *column,
				   GtkCellRenderer   *renderer,
				   GtkTreeModel      *model,
				   GtkTreeIter       *iter,
				   gpointer           data)
{
	gchar *name;
	gchar *desc;
	gchar *text;

	gtk_tree_model_get (model, iter,
			    NAME_COLUMN, &name,
			    DESC_COLUMN, &desc,
			    -1);

	if (desc != NULL)
	{
		text = g_markup_printf_escaped ("<b>%s</b> - %s",
						name,
						desc);
	}
	else
	{
		text = g_markup_printf_escaped ("<b>%s</b>",
						name);
	}

	g_free (name);
	g_free (desc);

	g_object_set (G_OBJECT (renderer),
		      "markup",
		      text,
		      NULL);

	g_free (text);
}
