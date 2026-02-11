cb_charges(GtkAction *action)
{
	GtkWidget  *dlg, *cwid, *scroll;
	GtkCellRenderer     *rend;
	GtkListStore	*clist_store;
	int	cnt;
	char	*pr;

	if  (!getselectedusers(1))
		return;

	clist_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_LONG);

	for  (cnt = 0;  cnt < pendunum;  cnt++)  {
		int_ugid_t	uu = ulist[pendulist[cnt]].spu_user;
		GtkTreeIter   iter;
		gtk_list_store_append(clist_store, &iter);
		gtk_list_store_set(clist_store, &iter, 0, prin_uname(uu), 1, (glong) calccharge(uu), -1);
	}

	pr = gprompt(1433);
	dlg = gtk_dialog_new_with_buttons(pr, GTK_WINDOW(toplevel), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
	free(pr);
	gtk_window_set_default_size(GTK_WINDOW(dlg), DEFAULT_CHG_WIDTH, DEFAULT_CHG_HEIGHT);
	cwid = gtk_tree_view_new();
	rend = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(cwid), -1, "User", rend, "text", 0, NULL);
	gtk_tree_view_column_set_resizable(gtk_tree_view_get_column(GTK_TREE_VIEW(cwid), 0), TRUE);
	rend = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(cwid), -1, "Charge", rend, "text", 1, NULL);
	gtk_tree_view_column_set_resizable(gtk_tree_view_get_column(GTK_TREE_VIEW(cwid), 1), TRUE);
	gtk_tree_view_set_model(GTK_TREE_VIEW(cwid), GTK_TREE_MODEL(clist_store));
	g_object_unref(clist_store);

	scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scroll), 5);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(scroll), cwid);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dlg)->vbox), scroll, FALSE, FALSE, 0);
	gtk_box_set_child_packing(GTK_BOX(GTK_DIALOG(dlg)->vbox), scroll, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_widget_show_all(dlg);

	gtk_dialog_run(GTK_DIALOG(dlg));
	gtk_widget_destroy(dlg);
}
