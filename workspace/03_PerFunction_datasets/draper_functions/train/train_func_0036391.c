addListOfAtoms(GtkWidget *vbox, GtkUIManager *manager)
{
	GtkWidget *scr;
	gint i;
	gint widall=0;
	gint widths[]={10};
	gint Factor=7;
	gint len = 1;

        GtkTreeStore *store;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeView *treeView;
	GtkTreeViewColumn *column;


	store = gtk_tree_store_new (1,G_TYPE_STRING);
        model = GTK_TREE_MODEL (store);

	for(i=0;i<len;i++) widall+=widths[i];

	widall=widall*Factor+40;

	scr=gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(scr,widall,(gint)(ScreenHeight*0.1));
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scr),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX (vbox), scr,TRUE, TRUE, 2);

	treeView = (GtkTreeView*)gtk_tree_view_new_with_model (model);
	gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeView), TRUE);
	gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (treeView), FALSE);
  	gtk_container_add(GTK_CONTAINER(scr),GTK_WIDGET(treeView));

	for (i=0;i<len;i++)
	{
		column = gtk_tree_view_column_new ();
		gtk_tree_view_column_set_title (column, "There atoms can do an hydrogen bonds");
		gtk_tree_view_column_set_min_width(column, widths[i]*Factor);
		gtk_tree_view_column_set_reorderable(column, TRUE);
		{
			GtkWidget*  t = gtk_tree_view_column_get_widget (column);
			if(t) gtk_widget_hide(t);
		}

		renderer = gtk_cell_renderer_text_new ();
		gtk_tree_view_column_pack_start (column, renderer, TRUE);
		gtk_tree_view_column_set_attributes (column, renderer, "text", 0, NULL);
		gtk_tree_view_append_column (GTK_TREE_VIEW (treeView), column);
	}

  	set_base_style(GTK_WIDGET(treeView),55000,55000,55000);
	gtk_widget_show (GTK_WIDGET(treeView));

	g_signal_connect (treeView, "button_press_event", G_CALLBACK (event_dispatcher2), manager);

	return treeView;
}
