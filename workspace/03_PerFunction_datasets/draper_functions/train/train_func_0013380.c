file_data_check_changed_single_file(FileData *fd, struct stat *st)
{
	if (fd->size != st->st_size ||
	    fd->date != st->st_mtime)
		{
		fd->size = st->st_size;
		fd->date = st->st_mtime;
		fd->mode = st->st_mode;
		if (fd->thumb_pixbuf) g_object_unref(fd->thumb_pixbuf);
		fd->thumb_pixbuf = NULL;
		file_data_increment_version(fd);
		file_data_send_notification(fd, NOTIFY_REREAD);
		return TRUE;
		}
	return FALSE;
}
