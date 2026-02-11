save_fits(GtkWidget *chooser, gpointer user_data)
{
	char *fn;
	struct file_action *fa = user_data;
	struct image_channel *ich;
	int i;

	fn = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
	g_return_if_fail(fn != NULL);

	d3_printf("Saving fits file: %s\n", fn);
	ich = fa->data;
	if (file_is_zipped(fn)) {
		for (i = strlen(fn); i > 0; i--)
			if (fn[i] == '.') {
				fn[i] = 0;
				break;
			}
		write_gz_fits_frame(ich->fr, fn, P_STR(FILE_COMPRESS));
	} else {
		write_fits_frame(ich->fr, fn);
	}

	g_free(fn);
}
