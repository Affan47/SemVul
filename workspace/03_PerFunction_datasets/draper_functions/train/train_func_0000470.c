image_notify_cb(FileData *fd, NotifyType type, gpointer data)
{
	ImageWindow *imd = data;

	if (!imd || !image_get_pixbuf(imd) ||

	    !imd->image_fd ||
	    imd->state == IMAGE_STATE_NONE
	    ) return;

	if ((type & NOTIFY_REREAD) && fd == imd->image_fd)
		{


		DEBUG_1("Notify image: %s %04x", fd->path, type);
		image_reload(imd);
		}
}
