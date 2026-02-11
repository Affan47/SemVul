glade_gtk_frame_post_create (GladeWidgetAdaptor *adaptor,
			     GObject            *frame,
			     GladeCreateReason   reason)
{
	static GladeWidgetAdaptor *label_adaptor = NULL, *alignment_adaptor = NULL;
	GladeWidget *gframe, *glabel, *galignment;
	GtkWidget *label;
	gchar     *label_text;

	if (reason != GLADE_CREATE_USER)
		return;

	g_return_if_fail (GTK_IS_FRAME (frame));
	gframe = glade_widget_get_from_gobject (frame);
	g_return_if_fail (GLADE_IS_WIDGET (gframe));


	if (((label = gtk_frame_get_label_widget (GTK_FRAME (frame))) == NULL ||
	    (glade_widget_get_from_gobject (label) == NULL)) &&
	    (GTK_IS_ASPECT_FRAME (frame) == FALSE))
	{

		if (label_adaptor == NULL)
			label_adaptor = glade_widget_adaptor_get_by_type (GTK_TYPE_LABEL);
		if (alignment_adaptor == NULL)
			alignment_adaptor = glade_widget_adaptor_get_by_type (GTK_TYPE_ALIGNMENT);


		glabel = glade_widget_adaptor_create_widget (label_adaptor, FALSE,
							   "parent", gframe,
							   "project", glade_widget_get_project (gframe),
							   NULL);

		label_text = g_strdup_printf ("<b>%s</b>", glade_widget_get_name (gframe));
		glade_widget_property_set (glabel, "label", label_text);
		glade_widget_property_set (glabel, "use-markup", "TRUE");
		g_free (label_text);

		g_object_set_data (glabel->object, "special-child-type", "label_item");
		glade_widget_add_child (gframe, glabel, FALSE);


		galignment = glade_widget_adaptor_create_widget (alignment_adaptor, FALSE,
						 	       "parent", gframe,
						               "project", glade_widget_get_project (gframe),
					                       NULL);

		glade_widget_property_set (galignment, "left-padding", 12);
		glade_widget_add_child (gframe, galignment, FALSE);
	}


	GWA_GET_CLASS (GTK_TYPE_CONTAINER)->post_create (adaptor, frame, reason);
}
