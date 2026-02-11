update_io_dialog(Children *children)
{
	GSList *cur;

	debug_print("Updating actions input/output dialog.\n");

	if (children->progress_bar) {
		gchar *text;
#ifdef GENERIC_UMPC

		const gchar *format = "%s %d/%d";
#else
		const gchar *format = "%s %d / %d";
#endif

		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(children->progress_bar),
						  (children->initial_nb == 0) ? 0 :
					      (gdouble) (children->initial_nb - children->nb) /
					      (gdouble) children->initial_nb);
		text = g_strdup_printf(format, _("Completed"),
				       children->initial_nb - children->nb,
				       children->initial_nb);
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(children->progress_bar), text);
		g_free(text);
	}

	if (!children->nb) {
		gtk_widget_set_sensitive(children->abort_btn, FALSE);
		gtk_widget_set_sensitive(children->close_btn, TRUE);
		if (children->input_hbox)
			gtk_widget_set_sensitive(children->input_hbox, FALSE);
		gtk_widget_grab_focus(children->close_btn);
		g_signal_connect(G_OBJECT(children->dialog),
				 "key_press_event",
				 G_CALLBACK(io_dialog_key_pressed_cb),
				 children);
	}

	if (children->output) {
		GtkWidget *text = children->text;
		GtkTextBuffer *textbuf;
		GtkTextIter iter, start_iter, end_iter;
		gchar *caption;
		ChildInfo *child_info;

		gtk_widget_show(children->scrolledwin);
		textbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
		gtk_text_buffer_get_bounds(textbuf, &start_iter, &end_iter);
		gtk_text_buffer_delete(textbuf, &start_iter, &end_iter);
		gtk_text_buffer_get_start_iter(textbuf, &iter);

		for (cur = children->list; cur; cur = cur->next) {
			child_info = (ChildInfo *)cur->data;
			if (child_info->pid)
				caption = g_strdup_printf
					(_("--- Running: %s\n"),
					 child_info->cmd);
			else
				caption = g_strdup_printf
					(_("--- Ended: %s\n"),
					 child_info->cmd);

			gtk_text_buffer_insert(textbuf, &iter, caption, -1);
			gtk_text_buffer_insert(textbuf, &iter,
					       child_info->output->str, -1);
			g_free(caption);
			child_info->new_out = FALSE;
		}
	}
}
