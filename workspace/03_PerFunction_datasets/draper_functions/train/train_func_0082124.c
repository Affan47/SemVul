allsel_cb(GtkAction *action, gpointer data)
{
	MainWindow *mainwin = (MainWindow *)data;
	MessageView *msgview = mainwin->messageview;

	if (messageview_is_visible(msgview) &&
		 (gtk_widget_has_focus(msgview->mimeview->textview->text)))
		messageview_select_all(mainwin->messageview);
	else
		summary_select_all(mainwin->summaryview);
}
