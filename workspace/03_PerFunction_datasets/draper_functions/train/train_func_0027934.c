_e2_dialog_resize_destroy_cb (GtkWidget *dialog, gpointer data)
{
	gpointer idle_id = g_object_get_data (G_OBJECT (dialog),
			"e2-dialog-resize-idle-id");
	if (idle_id != NULL)
	{
		g_source_remove (GPOINTER_TO_UINT(idle_id));
		g_object_set_data (G_OBJECT (dialog), "e2-dialog-resize-idle-id", NULL);
	}
}
