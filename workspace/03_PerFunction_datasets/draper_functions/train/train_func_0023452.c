add_item(const gchar *name)
{
	GtkTreeIter iter;
	gchar *fname, *utf8_name, *utf8_fullname;
	const gchar *sep;
	gboolean dir;

	if (G_UNLIKELY(! NZV(name)))
		return;


	sep = (utils_str_equal(current_dir, "/")) ? "" : G_DIR_SEPARATOR_S;
	fname = g_strconcat(current_dir, sep, name, NULL);
	dir = g_file_test(fname, G_FILE_TEST_IS_DIR);
	utf8_fullname = utils_get_locale_from_utf8(fname);
	utf8_name = utils_get_utf8_from_locale(name);
	g_free(fname);

	if (! show_hidden_files && check_hidden(utf8_fullname, utf8_name))
		goto done;

	if (dir)
	{
		if (last_dir_iter == NULL)
			gtk_list_store_prepend(file_store, &iter);
		else
		{
			gtk_list_store_insert_after(file_store, &iter, last_dir_iter);
			gtk_tree_iter_free(last_dir_iter);
		}
		last_dir_iter = gtk_tree_iter_copy(&iter);
	}
	else
	{
		if (! show_hidden_files && hide_object_files && check_object(utf8_name))
			goto done;
		if (check_filtered(utf8_name))
			goto done;

		gtk_list_store_append(file_store, &iter);
	}
	gtk_list_store_set(file_store, &iter,
		FILEVIEW_COLUMN_ICON, (dir) ? GTK_STOCK_DIRECTORY : GTK_STOCK_FILE,
		FILEVIEW_COLUMN_NAME, utf8_name,
		FILEVIEW_COLUMN_FILENAME, utf8_fullname,
		-1);
done:
	g_free(utf8_name);
	g_free(utf8_fullname);
}
