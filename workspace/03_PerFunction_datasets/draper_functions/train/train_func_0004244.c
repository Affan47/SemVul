gcm_print_with_render_callback (GcmPrint *print, GtkWindow *window, GcmPrintRenderCb render_callback, gpointer user_data, GError **error)
{
	GcmPrintPrivate *priv = print->priv;
	gboolean ret = TRUE;
	GcmPrintTask *task;
	GtkPrintOperation *operation;
	GtkPrintOperationResult res;


	task = g_new0 (GcmPrintTask, 1);
	task->print = g_object_ref (print);
	task->render_callback = render_callback;
	task->user_data = user_data;
	task->loop = g_main_loop_new (NULL, FALSE);


	operation = gtk_print_operation_new ();
	gtk_print_operation_set_print_settings (operation, priv->settings);
	g_signal_connect (operation, "begin-print", G_CALLBACK (gcm_print_begin_print_cb), task);
	g_signal_connect (operation, "draw-page", G_CALLBACK (gcm_print_draw_page_cb), task);
	g_signal_connect (operation, "status-changed", G_CALLBACK (gcm_print_status_changed_cb), task);
	g_signal_connect (operation, "done", G_CALLBACK (gcm_print_done_cb), task);


	gtk_print_operation_set_use_full_page (operation, FALSE);


	gtk_print_operation_set_show_progress (operation, FALSE);


	gtk_print_operation_set_support_selection (operation, FALSE);


	gtk_print_operation_set_track_print_status (operation, TRUE);


	gtk_print_operation_set_embed_page_setup (operation, TRUE);


	res = gtk_print_operation_run (operation,
				       GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
				       window, error);


	if (res == GTK_PRINT_OPERATION_RESULT_APPLY) {
		g_object_unref (priv->settings);
		priv->settings = g_object_ref (gtk_print_operation_get_print_settings (operation));
	}


	if (res == GTK_PRINT_OPERATION_RESULT_ERROR) {
		ret = FALSE;
		goto out;
	}


	g_main_loop_run (task->loop);


	if (task->error != NULL) {
		g_set_error_literal (error, 1, 0, task->error->message);
		ret = FALSE;
	}
out:
	if (task->filenames != NULL)
		g_ptr_array_unref (task->filenames);
	if (task->print != NULL)
		g_object_unref (task->print);
	if (task->loop != NULL)
		g_main_loop_unref (task->loop);
	if (task->error != NULL)
		g_error_free (task->error);
	g_free (task);
	g_object_unref (operation);
	return ret;
}
