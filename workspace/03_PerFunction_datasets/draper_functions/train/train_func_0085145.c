cmd_selectsuffix(MainInfo *min, DirPane *src, DirPane *dst, const CmdArg *ca)
{
	const gchar	*suff = NULL;
	GtkTreeModel	*m = dp_get_tree_model(src);

	if((suff = car_bareword_get(ca, 0)) != NULL)
		;
	if(suff == NULL)
	{
		GdkEventButton	*evt;
		GtkTreeIter	si;
		gboolean	siok = FALSE;

		if((evt = (GdkEventButton *) evt_event_get(GDK_BUTTON_PRESS)) != NULL)
		{
			GtkTreePath	*path = NULL;

			if(gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(src->view), evt->x, evt->y, &path, NULL, NULL, NULL) && path != NULL)
			{
				siok = gtk_tree_model_get_iter(m, &si, path);
				gtk_tree_path_free(path);
			}
		}
		else
			g_warning("Suffix selection from focused row is not implemented");
		if(siok)
		{
			const gchar	*dn = dp_row_get_name_display(dp_get_tree_model(src), (DirRow2 *) &si);
			suff = g_utf8_strrchr(dn, -1, '.');
		}
	}


	if(suff != NULL)
	{
		GtkTreeIter	iter;

		if(gtk_tree_model_get_iter_first(m, &iter))
		{
			guint	action;
			void	(*afunc)(DirPane *dp, const DirRow2 *row);

			action = car_keyword_get_enum(ca, "action", 0, "select", "unselect", "toggle", NULL);
			afunc = (action == 0) ? dp_select : (action == 1) ? dp_unselect : dp_toggle;
			do
			{
				if(stu_has_suffix(dp_row_get_name_display(m, &iter), suff))
					afunc(src, &iter);

			} while(gtk_tree_model_iter_next(m, &iter));
		}
	}
	return 1;
}
