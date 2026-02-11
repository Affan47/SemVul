set_image_style_cb ( GtkWidget *widget, AnypaperWindow *window )
{
	window->parameters->style = gtk_combo_box_get_active (GTK_COMBO_BOX (window->priv->combo));
	if (window->parameters->style == 5) gtk_widget_show (window->priv->custom_table);
	else gtk_widget_hide (window->priv->custom_table);
	set_image_common (window);
}
