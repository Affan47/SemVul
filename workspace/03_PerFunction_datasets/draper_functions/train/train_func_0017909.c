print_mimeview(MimeView *mimeview, gint sel_start, gint sel_end, gint partnum)
{
	MainWindow *mainwin;
	if (!mimeview
	||  !mimeview->textview
	||  !mimeview->textview->text)
		alertpanel_warning(_("Cannot print: the message doesn't "
				     "contain text."));
	else {
		gtk_widget_realize(mimeview->textview->text);
		if (partnum > 0) {
			mimeview_select_part_num(mimeview, partnum);
		}
		if (mimeview->type == MIMEVIEW_VIEWER) {
			MimeViewer *viewer = mimeview->mimeviewer;
			if (viewer && viewer->print) {
				viewer->print(viewer);
				return;
			}
		}
		if (sel_start != -1 && sel_end != -1) {
			GtkTextIter start, end;
			GtkTextView *text = GTK_TEXT_VIEW(mimeview->textview->text);
			GtkTextBuffer *buffer = gtk_text_view_get_buffer(text);

			gtk_text_buffer_get_iter_at_offset(buffer, &start, sel_start);
			gtk_text_buffer_get_iter_at_offset(buffer, &end, sel_end);
			gtk_text_buffer_select_range(buffer, &start, &end);
		}

		mainwin = mainwindow_get_mainwindow();
		printing_print(GTK_TEXT_VIEW(mimeview->textview->text),
			       mainwin ? GTK_WINDOW(mainwin->window) : NULL,
				sel_start, sel_end);
	}
}
