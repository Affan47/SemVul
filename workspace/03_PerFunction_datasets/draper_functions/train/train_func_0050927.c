vcal_event_exists(const gchar *id)
{
	MsgInfo *info = NULL;
	Folder *folder = folder_find_from_name ("vCalendar", vcal_folder_get_class());
	if (!folder)
		return FALSE;

	info = folder_item_get_msginfo_by_msgid(folder->inbox, id);
	if (info != NULL) {
		procmsg_msginfo_free(info);
		return TRUE;
	}
	return FALSE;
}
