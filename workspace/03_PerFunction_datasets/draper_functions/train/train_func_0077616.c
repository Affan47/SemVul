dupe_item_find_path(DupeWindow *dw, const gchar *path)
{
	DupeItem *di;

	di = dupe_item_find_path_by_list(path, dw->list);
	if (!di && dw->second_set) di = dupe_item_find_path_by_list(path, dw->second_list);

	return di;
}
