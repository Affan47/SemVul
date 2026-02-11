cb_tree_selection_changed(GtkTreeSelection *selection, gpointer data)
	{
	GtkTreeIter		iter;
	GtkTreeModel	*model;
	GtkTreePath		*path;
	FSmon			*fs;
	gint			*indices, depth, secondary;

	if (!gtk_tree_selection_get_selected(selection, &model, &iter))
		{
		reset_entries(FALSE);
		gtk_button_set_label(GTK_BUTTON(new_apply_button), GTK_STOCK_NEW);
		gtk_widget_set_sensitive(delete_button, FALSE);
		gtk_widget_set_sensitive(alert_button, FALSE);
		return;
		}
	path = gtk_tree_model_get_path(model, &iter);
	indices = gtk_tree_path_get_indices(path);
	secondary = indices[0];
	depth = gtk_tree_path_get_depth(path);


	change_row_reference(model, path);
	gtk_tree_path_free(path);

	if (depth == 1)
		{
		reset_entries(secondary);
		gtk_button_set_label(GTK_BUTTON(new_apply_button), GTK_STOCK_NEW);
		gtk_widget_set_sensitive(delete_button, FALSE);
		gtk_widget_set_sensitive(alert_button, FALSE);
		return;
		}
	gtk_button_set_label(GTK_BUTTON(new_apply_button), GTK_STOCK_APPLY);
	gtk_widget_set_sensitive(delete_button, TRUE);
	gtk_widget_set_sensitive(alert_button, TRUE);

	fs = fs_new_from_model(model, &iter);
	if (!secondary)
		fs->show_if_mounted = FALSE;

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(secondary_button),
					secondary);
	gtk_entry_set_text(GTK_ENTRY(label_entry), fs->label);
	gtk_entry_set_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(dir_combo_box))),
			fs->mount.directory);
	if (show_button)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(show_button),
					fs->show_if_mounted);
	if (mounting_button)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mounting_button),
					fs->fstab_mounting);
	if (ejectable_button)
		{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ejectable_button),
					fs->ejectable);
		if (device_entry)
			{
			gtk_entry_set_text(GTK_ENTRY(device_entry), fs->eject_device);
			if (!fs->ejectable)
				gtk_widget_set_sensitive(device_entry, FALSE);
			}
		}
	if (mount_entry)
		{
		gtk_entry_set_text(GTK_ENTRY(mount_entry), fs->launch_mount.command);
		gtk_entry_set_text(GTK_ENTRY(umount_entry), fs->launch_umount.command);
		}
	free_fsmon_strings(fs);
	g_free(fs);
	}
