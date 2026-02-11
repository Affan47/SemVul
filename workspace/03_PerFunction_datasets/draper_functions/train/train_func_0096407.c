collection_dialog_save_close(gchar *path, CollectionData *cd)
{
	if (!path) path = cd->path;
	if (!path) path = cd->name;

	collection_save_or_load_dialog(path, DIALOG_SAVE_CLOSE, cd);
}
