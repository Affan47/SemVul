mh_item_close(Folder *folder, FolderItem *item)
{
	time_t last_mtime = (time_t)0;
	gboolean need_scan = mh_scan_required(item->folder, item);
	last_mtime = item->mtime;

	mh_write_sequences(item, FALSE);

	if (item->mtime == last_mtime && !need_scan) {
		mh_set_mtime(folder, item);
	}

	return 0;
}
