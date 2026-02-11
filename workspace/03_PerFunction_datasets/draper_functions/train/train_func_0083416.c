on_column_popup_toggled(GtkCheckMenuItem *checkmenuitem, gpointer user_data)
{
    GtkColumnChooser * cc;

    g_return_if_fail(user_data != NULL);
    g_return_if_fail(GTK_IS_COLUMN_CHOOSER(user_data));

    cc = GTK_COLUMN_CHOOSER(user_data);

#if (GTK_MAJOR_VERSION >= 2)
    gtk_tree_view_column_set_visible(
		(GtkTreeViewColumn *) gtk_column_chooser_get_column(cc,
									GTK_WIDGET(checkmenuitem)),
		checkmenuitem->active);
#else
    gtk_clist_set_column_visibility(GTK_CLIST(cc->widget),
         GPOINTER_TO_INT(
			gtk_column_chooser_get_column(cc, GTK_WIDGET(checkmenuitem))),
         checkmenuitem->active);
#endif
}
