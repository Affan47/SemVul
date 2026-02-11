vflist_dnd_end(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	ViewFile *vf = data;

	vflist_color_set(vf, VFLIST(vf)->click_fd, FALSE);

	if (context->action == GDK_ACTION_MOVE)
		{
		vf_refresh(vf);
		}
}
