templates_save_recurse_func(GNode *node, gpointer data)
{
	FolderItem *item = (FolderItem *) node->data;
	FolderItemTemplatesPage *page = (FolderItemTemplatesPage *) data;

	cm_return_val_if_fail(item != NULL, TRUE);
	cm_return_val_if_fail(page != NULL, TRUE);

	templates_save_folder_prefs(item, page);


	if ((node == page->item->node) &&
	    !(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->new_msg_format_rec_checkbtn)) ||
	      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->reply_format_rec_checkbtn)) ||
	      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(page->forward_format_rec_checkbtn))))
		return TRUE;
	else
		return FALSE;

	return FALSE;
}
