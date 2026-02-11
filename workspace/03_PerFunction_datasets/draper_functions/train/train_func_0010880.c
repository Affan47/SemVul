process_cb(GtkAction *action, gpointer data)
{
	MainWindow *mainwin = (MainWindow *)data;
	FolderItem *item = mainwin->summaryview->folder_item;
	cm_return_if_fail(item != NULL);

	item->processing_pending = TRUE;
	folder_item_apply_processing(item);
	item->processing_pending = FALSE;
}
