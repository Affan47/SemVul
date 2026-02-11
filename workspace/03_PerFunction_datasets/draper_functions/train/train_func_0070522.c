vf_pop_menu_edit_cb(GtkWidget *widget, gpointer data)
{
	ViewFile *vf;
	const gchar *key = data;

	vf = submenu_item_get_data(widget);

	if (!vf) return;

	file_util_start_editor_from_filelist(key, vf_pop_menu_file_list(vf), vf->dir_fd->path, vf->listview);
}
