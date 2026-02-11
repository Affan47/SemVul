glade_gtk_image_set_property (GladeWidgetAdaptor *adaptor,
			      GObject            *object,
			      const gchar        *id,
			      const GValue       *value)
{
	if (!strcmp (id, "image-mode"))
		glade_gtk_image_set_image_mode (object, value);
	else if (!strcmp (id, "icon-size"))
	{

		GValue int_value = { 0, };
		g_value_init (&int_value, G_TYPE_INT);
		g_value_set_int (&int_value, g_value_get_enum (value));
		GWA_GET_CLASS (GTK_TYPE_WIDGET)->set_property (adaptor, object, id, &int_value);
		g_value_unset (&int_value);
	}
	else
	{
		GladeWidget *widget = glade_widget_get_from_gobject (object);
		GladeImageEditMode mode = 0;

		glade_widget_property_get (widget, "image-mode", &mode);


		switch (mode)
		{
		case GLADE_IMAGE_MODE_STOCK:
			if (!strcmp (id, "icon-name") ||
			    !strcmp (id, "pixbuf"))
				return;
			break;
		case GLADE_IMAGE_MODE_ICON:
			if (!strcmp (id, "stock") ||
			    !strcmp (id, "pixbuf"))
				return;
			break;
		case GLADE_IMAGE_MODE_FILENAME:
			if (!strcmp (id, "stock") ||
			    !strcmp (id, "icon-name"))
				return;
		default:
			break;
		}

		GWA_GET_CLASS (GTK_TYPE_WIDGET)->set_property (adaptor, object,
							       id, value);
	}
}
