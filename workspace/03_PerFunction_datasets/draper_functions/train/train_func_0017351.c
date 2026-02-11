gst_tool_init (GstTool *tool)
{
	GdkPixbuf  *pixbuf;
	GtkBuilder *builder;

	tool->icon_theme = gtk_icon_theme_get_default ();
	tool->common_ui_path  = INTERFACES_DIR "/common.ui";

	tool->session = oobs_session_get ();

	builder = gst_tool_load_common_ui (tool);

	tool->report_window = GTK_WIDGET (gtk_builder_get_object (builder, "report_window"));
	tool->report_label = GTK_WIDGET (gtk_builder_get_object (builder, "report_label"));
	tool->report_progress = GTK_WIDGET (gtk_builder_get_object (builder, "report_progress"));
	tool->report_pixmap = GTK_WIDGET (gtk_builder_get_object (builder, "report_pixmap"));
	g_signal_connect (G_OBJECT (tool->report_window), "delete_event",
			  G_CALLBACK (report_window_close_cb), tool);

	pixbuf = gtk_icon_theme_load_icon (tool->icon_theme, "gnome-system-config", 48, 0, NULL);
	gtk_image_set_from_pixbuf (GTK_IMAGE (tool->report_pixmap), pixbuf);

	if (pixbuf)
		g_object_unref (pixbuf);

	tool->objects = g_ptr_array_new ();

	g_object_unref (builder);
}
