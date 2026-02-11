eject_shortcut_cb (GtkMenuItem           *item,
		   NemoPlacesSidebar *sidebar)
{
	GtkTreeIter iter;
	GMount *mount;
	GVolume *volume;
	GDrive *drive;

	if (!get_selected_iter (sidebar, &iter)) {
		return;
	}

	gtk_tree_model_get (GTK_TREE_MODEL (sidebar->store), &iter,
			    PLACES_SIDEBAR_COLUMN_MOUNT, &mount,
			    PLACES_SIDEBAR_COLUMN_VOLUME, &volume,
			    PLACES_SIDEBAR_COLUMN_DRIVE, &drive,
			    -1);

	do_eject (mount, volume, drive, sidebar);
}
