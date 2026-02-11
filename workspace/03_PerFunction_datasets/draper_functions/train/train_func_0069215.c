banlist_unban_inner (gpointer none, banlist_info *banl, int mode_num)
{
	session *sess = banl->sess;
	GtkTreeModel *model;
	GtkTreeSelection *sel;
	GtkTreeIter iter;
	char tbuf[2048];
	char **masks, *mask, *type;
	int num_sel, i;


	model = GTK_TREE_MODEL (get_store (sess));
	sel = gtk_tree_view_get_selection (get_view (sess));

	if (!gtk_tree_model_get_iter_first (model, &iter))
		return 0;

	masks = g_malloc (sizeof (char *) * banl->line_ct);
	num_sel = 0;
	do
	{
		if (gtk_tree_selection_iter_is_selected (sel, &iter))
		{

			gtk_tree_model_get (model, &iter, TYPE_COLUMN, &type, MASK_COLUMN, &mask, -1);


			if (strcmp (_(modes[mode_num].type), type) != 0)
				continue;


			masks[num_sel++] = g_strdup (mask);
			g_free (mask);
			g_free (type);
		}
	}
	while (gtk_tree_model_iter_next (model, &iter));


	if (num_sel)
		send_channel_modes (sess, tbuf, masks, 0, num_sel, '-', modes[mode_num].letter, 0);


	for (i=0; i < num_sel; i++)
		g_free (masks[i]);
	g_free (masks);

	return num_sel;
}
