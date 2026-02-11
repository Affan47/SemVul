image_osd_notify_cb(FileData *fd, NotifyType type, gpointer data)
{
	OverlayStateData *osd = data;

	if ((type & (NOTIFY_HISTMAP)) && osd->imd && fd == osd->imd->image_fd)
		{
		DEBUG_1("Notify osd: %s %04x", fd->path, type);
		osd->notify |= type;
		image_osd_update_schedule(osd, FALSE);
		}
}
