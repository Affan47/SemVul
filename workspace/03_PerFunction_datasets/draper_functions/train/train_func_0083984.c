file_util_details_dialog_exclude(GenericDialog *gd, gpointer data, gboolean discard)
{
	UtilityData *ud = data;
	FileData *fd = g_object_get_data(G_OBJECT(gd->dialog), "file_data");

	if (!fd) return;
	file_util_exclude_fd(ud, fd);

	if (discard && ud->discard_func) ud->discard_func(fd);


	if (!ud->flist)
		{

		g_signal_handlers_disconnect_by_func(ud->gd->dialog, G_CALLBACK(file_util_details_dialog_close_cb), gd->dialog);
		g_signal_handlers_disconnect_by_func(gd->dialog, G_CALLBACK(file_util_details_dialog_destroy_cb), ud);

		file_util_cancel_cb(ud->gd, ud);
		}
}
