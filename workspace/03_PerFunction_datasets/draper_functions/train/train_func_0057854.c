size_allocate_cb(GtkWidget *widget,
					 GtkAllocation *allocation,
					 gpointer data)
{
	gint *prefs_logwin_width = NULL;
	gint *prefs_logwin_height = NULL;
	LogInstance instance = GPOINTER_TO_INT(data);

	cm_return_if_fail(allocation != NULL);

	get_log_prefs(instance, &prefs_logwin_width, &prefs_logwin_height);
	cm_return_if_fail(prefs_logwin_width != NULL);
	cm_return_if_fail(prefs_logwin_height != NULL);

	*prefs_logwin_width = allocation->width;
	*prefs_logwin_height = allocation->height;
}
