evt_style_add_clicked(GtkWidget *wid, gpointer user)
{
	P_Styles	*page = user;

	if(page != NULL)
	{
		Style		*stl, *parent;
		GtkTreeIter	iter;

		stl = stl_style_new_unique_name(page->si);

		if((parent = style_get_selected(page, &iter)) == NULL)
			parent = stl_styleinfo_style_root(page->si);
		stl_styleinfo_style_add(page->si, parent, stl);
		stl_style_set_expand(parent, TRUE);
		populate_tree(page);
		if(stl_styleinfo_tree_find_style(page->si, page->store, stl, &iter))
		{
			gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(page->tree)), &iter);
			gtk_editable_select_region(GTK_EDITABLE(page->dname), 0, -1);
			gtk_widget_grab_focus(page->dname);
		}
	}
}
