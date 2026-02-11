gcm_print_begin_print_cb (GtkPrintOperation *operation, GtkPrintContext *context, GcmPrintTask *task)
{
	GtkPageSetup *page_setup;


	page_setup = gtk_print_context_get_page_setup (context);


	task->filenames = task->render_callback (task->print, page_setup, task->user_data, &task->error);
	if (task->filenames == NULL) {
		gtk_print_operation_cancel (operation);
		goto out;
	}


	g_debug ("setting %i pages", task->filenames->len);
	gtk_print_operation_set_n_pages (operation, task->filenames->len);
out:
	return;
}
