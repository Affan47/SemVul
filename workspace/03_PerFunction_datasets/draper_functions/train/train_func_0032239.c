view_source_cb(GtkAction *action, gpointer data)
{
	MessageView *messageview = (MessageView *)data;
	SourceWindow *srcwin;

	if (!messageview->msginfo) return;

	srcwin = source_window_create();
	source_window_show_msg(srcwin, messageview->msginfo);
	source_window_show(srcwin);
}
