gtk_menu_option_init (GTypeInstance *instance, gpointer g_class)
{
	GtkMenuOption *menu = GTK_MENU_OPTION (instance);

	menu->priv = g_new0 (GtkMenuOptionPrivate, 1);
	menu->priv->array = g_array_new (FALSE, TRUE, sizeof (guint));
	menu->priv->items = g_ptr_array_new ();
}
