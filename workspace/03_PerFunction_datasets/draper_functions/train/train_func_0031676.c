vflist_pop_menu_thumbs_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf = data;

	vflist_color_set(vf, VFLIST(vf)->click_fd, FALSE);
	if (vf->layout)
		{
		layout_thumb_set(vf->layout, !VFLIST(vf)->thumbs_enabled);
		}
	else
		{
		vflist_thumb_set(vf, !VFLIST(vf)->thumbs_enabled);
		}
}
