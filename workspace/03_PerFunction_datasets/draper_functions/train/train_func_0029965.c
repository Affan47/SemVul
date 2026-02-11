layout_image_new(LayoutWindow *lw, gint i)
{
	if (!lw->split_image_sizegroup) lw->split_image_sizegroup = gtk_size_group_new(GTK_SIZE_GROUP_BOTH);

	if (!lw->split_images[i])
		{
		lw->split_images[i] = image_new(TRUE);

#if GTK_CHECK_VERSION(2,12,0)
		g_object_ref(lw->split_images[i]->widget);
#else
		gtk_widget_ref(lw->split_images[i]->widget);
#endif

		g_signal_connect(G_OBJECT(lw->split_images[i]->pr), "update-pixel",
				 G_CALLBACK(layout_status_update_pixel_cb), lw);

		image_background_set_color_from_options(lw->split_images[i], FALSE);

		image_auto_refresh_enable(lw->split_images[i], TRUE);

		layout_image_dnd_init(lw, i);
		image_color_profile_set(lw->split_images[i],
					options->color_profile.input_type,
					options->color_profile.use_image);
		image_color_profile_set_use(lw->split_images[i], options->color_profile.enabled);

		gtk_size_group_add_widget(lw->split_image_sizegroup, lw->split_images[i]->widget);
		gtk_widget_set_size_request(lw->split_images[i]->widget, IMAGE_MIN_WIDTH, -1);

		image_set_focus_in_func(lw->split_images[i], layout_image_focus_in_cb, lw);

		}

	return lw->split_images[i]->widget;
}
