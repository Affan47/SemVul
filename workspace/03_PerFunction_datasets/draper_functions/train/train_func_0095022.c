cb_pl_button_track_pressed(GtkWidget *widget, gpointer userdata)
{
	xmmsc_result_t *res;
	struct params  *p;

	p = g_malloc(sizeof(struct params));
	p->gml = (GMedialib *)userdata;

	if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(p->gml->playlist.ls),
	                                  &(p->iter))) {
		res = xmmsc_playlist_current_pos(connection, NULL);
		xmmsc_result_notifier_set(res, n_playlist_current_pos, p);
		xmmsc_result_unref(res);
	}
}
