bar_event(GtkWidget *bar, GdkEvent *event)
{
	BarData *bd;
	GList *list, *work;
	gboolean ret = FALSE;

	bd = g_object_get_data(G_OBJECT(bar), "bar_data");
	if (!bd) return FALSE;

	list = gtk_container_get_children(GTK_CONTAINER(bd->vbox));

	work = list;
	while (work)
		{
		GtkWidget *widget = gtk_bin_get_child(GTK_BIN(work->data));
		PaneData *pd = g_object_get_data(G_OBJECT(widget), "pane_data");
		if (!pd) continue;

		if (pd->pane_event && pd->pane_event(widget, event))
			{
			ret = TRUE;
			break;
			}
		work = work->next;
		}
	g_list_free(list);
	return ret;
}
