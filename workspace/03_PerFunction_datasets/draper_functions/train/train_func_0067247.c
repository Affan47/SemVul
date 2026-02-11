desktop_link_finalize (GObject *object)
{
	NemoDesktopLink *link;

	link = NEMO_DESKTOP_LINK (object);

	if (link->details->signal_handler != 0) {
		g_signal_handler_disconnect (link->details->signal_handler_obj,
					     link->details->signal_handler);
	}

	if (link->details->icon_file != NULL) {
		nemo_desktop_icon_file_remove (link->details->icon_file);
		nemo_file_unref (NEMO_FILE (link->details->icon_file));
		link->details->icon_file = NULL;
	}

	if (link->details->type == NEMO_DESKTOP_LINK_MOUNT) {
		g_object_unref (link->details->mount);
	}

	g_free (link->details->filename);
	g_free (link->details->display_name);
	if (link->details->activation_location) {
		g_object_unref (link->details->activation_location);
	}
	if (link->details->icon) {
		g_object_unref (link->details->icon);
	}

	G_OBJECT_CLASS (nemo_desktop_link_parent_class)->finalize (object);
}
