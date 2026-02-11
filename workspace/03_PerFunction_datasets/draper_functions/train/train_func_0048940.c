gui_gtk_switch_new(void)
{
	GtkWidget *_switch;
	GtkWidget *icon;

	_switch = GTK_WIDGET(g_object_new(GUIGTKSWITCH_TYPE, NULL));
	GTK_WIDGET_UNSET_FLAGS(_switch, GTK_CAN_FOCUS);

	gtk_button_set_label(GTK_BUTTON(_switch), "Switch");
	icon = gtk_image_new_from_stock("gtk-yes", GTK_ICON_SIZE_BUTTON);
	gtk_button_set_image(GTK_BUTTON(_switch), icon);

	return GTK_WIDGET(_switch);
}
