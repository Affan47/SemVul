toolbar_learn(gpointer data, guint as_spam)
{
	ToolbarItem *toolbar_item = (ToolbarItem*)data;
	MainWindow *mainwin;
	MessageView *msgview;

	cm_return_if_fail(toolbar_item != NULL);

	switch (toolbar_item->type) {
	case TOOLBAR_MAIN:
		mainwin = (MainWindow*)toolbar_item->parent;
		if (as_spam)
			mainwindow_learn(mainwin, TRUE);
		else
			mainwindow_learn(mainwin, FALSE);
		break;
	case TOOLBAR_MSGVIEW:
		msgview = (MessageView*)toolbar_item->parent;
		if (as_spam)
			messageview_learn(msgview, TRUE);
		else
			messageview_learn(msgview, FALSE);
		break;
	default:
		debug_print("toolbar event not supported\n");
	}
}
