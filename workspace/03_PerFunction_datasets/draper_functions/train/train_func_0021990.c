pevent_save_cb (GtkWidget * wid, void *data)
{
	if (data)
	{
		gtkutil_file_req (_("Print Texts File"), pevent_save_req_cb, NULL,
								NULL, NULL, FRF_WRITE);
		return;
	}
	pevent_save (NULL);
}
