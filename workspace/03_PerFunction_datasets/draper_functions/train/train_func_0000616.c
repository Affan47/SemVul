sort_string(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer userdata)
{
        gchar	*name1, *name2;
	gint	ret = 0;
	gint	colnum = GPOINTER_TO_INT(userdata);

        gtk_tree_model_get(model, a, colnum, &name1, -1);
        gtk_tree_model_get(model, b, colnum, &name2, -1);

	if  (!name1  ||  !name2)  {
		if  (!name1  &&  !name2)
			return  0;
		if  (!name1)  {
			g_free(name2);
			return  -1;
		}
		else  {
			g_free(name1);
			return  1;
		}
	}

	ret = g_utf8_collate(name1, name2);
	g_free(name1);
	g_free(name2);
	return  ret;
}
