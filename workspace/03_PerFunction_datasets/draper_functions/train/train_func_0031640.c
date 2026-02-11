histogram_notify_cb(FileData *fd, NotifyType type, gpointer data)
{
	if ((type & NOTIFY_REREAD) && fd->histmap)
		{
		DEBUG_1("Notify histogram: %s %04x", fd->path, type);
		histmap_free(fd->histmap);
		fd->histmap = NULL;
		}
}
