ch_util_startup_cb (GApplication *application, ChCcmxPrivate *priv)
{
	GError *error = NULL;
	gint retval;
	GtkWidget *main_window;
	GtkWidget *widget;
	GPtrArray *array;


	priv->builder = gtk_builder_new ();
	retval = gtk_builder_add_from_file (priv->builder,
					    CH_DATA "/ch-spectro-util.ui",
					    &error);
	if (retval == 0) {
		g_warning ("failed to load ui: %s",
			   error->message);
		g_error_free (error);
		goto out;
	}


	gtk_icon_theme_append_search_path (gtk_icon_theme_get_default (),
					   CH_DATA G_DIR_SEPARATOR_S "icons");

	main_window = GTK_WIDGET (gtk_builder_get_object (priv->builder, "dialog_util"));
	gtk_application_add_window (priv->application, GTK_WINDOW (main_window));
	gtk_widget_set_size_request (main_window, 400, 100);


	gtk_widget_hide (main_window);


	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "button_close"));
	g_signal_connect (widget, "clicked",
			  G_CALLBACK (ch_util_close_button_cb), priv);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "button_refresh"));
	g_signal_connect (widget, "clicked",
			  G_CALLBACK (ch_util_refresh_button_cb), priv);
	widget = GTK_WIDGET (gtk_builder_get_object (priv->builder, "switch_auto_update"));
	g_signal_connect (widget, "notify::active",
			  G_CALLBACK (ch_util_auto_update_changed_cb), priv);


	ch_util_add_graphs (priv);
{
	ChPointObj *point;
	array = g_ptr_array_new_with_free_func ((GDestroyNotify) ch_point_obj_free);
	point = ch_point_obj_new ();
	point->x = 300;
	point->y = 2.2;
	point->color = 0xff0000;
	g_ptr_array_add (array, point);
	point = ch_point_obj_new ();
	point->x = 600;
	point->y = 1.8;
	point->color = 0xff0000;
	g_ptr_array_add (array, point);
	point = ch_point_obj_new ();
	point->x = 800;
	point->y = 1.2;
	point->color = 0xff0000;
	g_ptr_array_add (array, point);
	ch_graph_widget_assign (CH_GRAPH_WIDGET (priv->graph_result),
				 CH_GRAPH_WIDGET_PLOT_BOTH,
				 array);
	g_ptr_array_unref (array);
}

	g_usb_device_list_coldplug (priv->device_list);


	if (g_getenv ("COLORHUG_EMULATE") != NULL) {
		priv->device = ch_util_get_fake_device (priv);
		ch_util_got_device (priv);
	}


	gtk_widget_show (main_window);
out:
	return;
}
