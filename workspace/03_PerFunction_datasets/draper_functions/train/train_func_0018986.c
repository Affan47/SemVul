gtk_column_chooser_class_init(gpointer g_class, gpointer unused_class_data)
{
    GObjectClass *object_class;
    GtkWidgetClass *widget_class;
    GtkMenuShellClass *menu_shell_class;

	(void) unused_class_data;
    g_return_if_fail(g_class != NULL);

    parent_class = gtk_type_class(GTK_TYPE_MENU);
    object_class = G_OBJECT_CLASS(g_class);
    widget_class = GTK_WIDGET_CLASS(g_class);
    menu_shell_class = GTK_MENU_SHELL_CLASS(g_class);
    widget_class->button_press_event = gtk_column_chooser_button_press;
    menu_shell_class->deactivate = gtk_column_chooser_deactivate;
	object_class->finalize = gtk_column_chooser_finalize;
}
