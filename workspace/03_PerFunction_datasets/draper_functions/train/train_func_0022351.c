toolbar_close_cb(GtkWidget *widget, gpointer data)
{
	ToolbarItem *toolbar_item = (ToolbarItem*)data;
	MainWindow *mainwin;
	MessageView *messageview;
	Compose *compose;

	cm_return_if_fail(toolbar_item != NULL);

	switch (toolbar_item->type) {
	case TOOLBAR_MAIN:
		mainwin = (MainWindow *) toolbar_item->parent;
		app_will_exit(NULL, mainwin);
		break;
	case TOOLBAR_MSGVIEW:
		messageview = (MessageView *)toolbar_item->parent;
		messageview_destroy(messageview);
		break;
	case TOOLBAR_COMPOSE:
		compose = (Compose *)toolbar_item->parent;
		compose_close_toolbar(compose);
		break;
	}
}
