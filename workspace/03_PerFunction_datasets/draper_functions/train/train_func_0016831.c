folder_item_update_thaw(void)
{
	if (folder_item_update_freeze_cnt > 0)
		folder_item_update_freeze_cnt--;
	if (folder_item_update_freeze_cnt == 0) {

		folder_func_to_all_folders(folder_item_update_func, NULL);
	}
}
