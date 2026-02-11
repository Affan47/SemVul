on_selection_changed(G_GNUC_UNUSED GtkTreeSelection *selection, GtkWidget *menu)
{
	if (gtk_widget_get_visible(menu))
		gtk_menu_popdown(GTK_MENU(menu));
}
