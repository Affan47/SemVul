glade_palette_item_button_press (GtkWidget      *button,
				  GdkEventButton *event,
				  GladePalette   *item)
{
	if (glade_popup_is_popup_event (event))
	{
		GladeWidgetAdaptor *adaptor;

		adaptor = g_object_get_data (G_OBJECT (item), "glade-widget-adaptor");

		glade_popup_palette_pop (adaptor, event);
		return TRUE;
	}

	return FALSE;
}
