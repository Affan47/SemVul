update_data_model_real (GdaDataModelDir *model, const gchar *rel_path)
{
	GDir *dir;
	GError *error = NULL;
	const gchar *raw_filename;
	gchar *complete_dir;

	complete_dir = g_build_path (G_DIR_SEPARATOR_S, model->priv->basedir, rel_path, NULL);
	dir = g_dir_open (complete_dir, 0, &error);
	if (!dir) {
		add_error (model, error && error->message ? error->message : _("No detail"));
		g_error_free (error);
		g_free (complete_dir);
		return;
	}

	raw_filename = g_dir_read_name (dir);
	while (raw_filename) {
		gchar *complete_filename;
		complete_filename = g_build_filename (complete_dir, raw_filename, NULL);

		if (g_file_test (complete_filename, G_FILE_TEST_IS_DIR)) {


			if (*raw_filename != '.') {
				gchar *path;

				path = g_build_path (G_DIR_SEPARATOR_S, rel_path, raw_filename, NULL);
				update_data_model_real (model, path);
				g_free (path);
			}
		}
		else {

			if (*raw_filename != '.') {
				gchar *utf8_filename;
#ifndef G_OS_WIN32

				utf8_filename = g_strdup (raw_filename);
#else
				utf8_filename = g_strdup (raw_filename);
#endif
				FileRow *row;
				model->priv->upd_row ++;

				if (model->priv->upd_row < (int)model->priv->rows->len) {
					row = g_ptr_array_index (model->priv->rows, model->priv->upd_row);
					file_row_clean (row);
				}
				else
					row = file_row_new ();
				row->reldir = g_strdup (rel_path);
#ifndef G_OS_WIN32
				row->raw_filename_value = g_strdup (raw_filename);
#else
				row->raw_filename_value = NULL;
#endif
				g_value_take_string (row->filename_value = gda_value_new (G_TYPE_STRING),
						     utf8_filename);


				update_file_size (row, complete_filename);


				row->mime_value = NULL;
				row->md5sum_value = NULL;
				row->data_value = NULL;


				if (model->priv->upd_row < (int)model->priv->rows->len)
					gda_data_model_row_updated ((GdaDataModel *) model, model->priv->upd_row);
				else {
					g_ptr_array_add (model->priv->rows, row);
					gda_data_model_row_inserted ((GdaDataModel *) model,
								     model->priv->rows->len - 1);
				}
			}
		}
		g_free (complete_filename);

		raw_filename = g_dir_read_name (dir);
	}

	g_free (complete_dir);
	g_dir_close (dir);
}
