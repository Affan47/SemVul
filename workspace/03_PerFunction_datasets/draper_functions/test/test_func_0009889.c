on_files_key_press_event(GtkWidget *unused_widget,
	GdkEventKey *event, void *unused_udata)
{
	unsigned modifier;

	(void) unused_widget;
	(void) unused_udata;

	modifier = gtk_accelerator_get_default_mod_mask() & event->state;
	switch (event->keyval) {
	case GDK_Delete:
		if (0 == modifier) {
			switch (current_page) {
			case nb_downloads_page_finished:
			case nb_downloads_page_seeding:
				fi_gui_purge_selected_files();
				return TRUE;
			default:
				break;
			}
		}
		break;
	}
	return FALSE;
}
