gsr_quit (void)
{
	GList *p;

	for (p = windows; p;) {
		GSRWindow *window = p->data;


		p = p->next;

		if (gsr_window_is_saved (window) || gsr_discard_confirmation_dialog (window, TRUE))
			gsr_window_close (window);
	}
}
