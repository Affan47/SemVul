finish_build(gpointer user_data) {

	build_store_t * data = (build_store_t *)user_data;

	if (data->prog_window) {
		unregister_toplevel_window(data->prog_window);
		gtk_widget_destroy(data->prog_window);
		data->prog_window = NULL;
	}

        build_store_free(data);

	build_busy = 0;

	return FALSE;
}
