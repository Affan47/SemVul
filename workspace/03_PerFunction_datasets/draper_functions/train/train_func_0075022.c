create_window (void)
{
	GtkWidget		*window;
	GtkWidget		*widget;
	GtkWidget		*drawing;
	GtkBuilder		*builder;

	builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, UI_FILE, NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
	g_assert ( window );

    widget = GTK_WIDGET (gtk_builder_get_object (builder, "flip_roate_dialog"));
    drawing = GTK_WIDGET (gtk_builder_get_object (builder, "cv_drawing"));
	g_object_set_data(G_OBJECT(drawing), "flip_roate_dialog", widget);

	file_set_parent_window ( GTK_WINDOW(window) );
    gtk_builder_connect_signals (builder, NULL);

	init_eraser (builder);
	init_paint_brush (builder);
	save_the_children (builder);

    g_object_unref (G_OBJECT (builder));


	gtk_widget_show_all(window);

	return window;
}
