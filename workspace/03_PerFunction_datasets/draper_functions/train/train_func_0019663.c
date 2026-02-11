glade_gtk_menu_shell_add_child (GladeWidgetAdaptor  *adaptor,
			       GObject             *object,
			       GObject             *child)
{

	g_return_if_fail (GTK_IS_MENU_SHELL (object));
	g_return_if_fail (GTK_IS_MENU_ITEM (child));

	gtk_menu_shell_append (GTK_MENU_SHELL (object), GTK_WIDGET (child));
}
