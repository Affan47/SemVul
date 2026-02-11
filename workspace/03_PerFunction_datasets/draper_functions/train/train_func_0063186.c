view_new_window_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	CollectionData *cd;
	CollectInfo *info;

	cd = image_get_collection(vw->imd, &info);

	if (cd && info)
		{
		view_window_new_from_collection(cd, info);
		}
	else
		{
		view_window_new(image_get_fd(vw->imd));
		}
}
