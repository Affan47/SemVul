FileProcess (const gchar* filename, const gchar* mime_type, bool bSave, G_GNUC_UNUSED GtkWindow *window, G_GNUC_UNUSED Document *pDoc)
{
	if(bSave) {
		GFile *file = g_file_new_for_uri (filename);
		bool err = g_file_query_exists (file, NULL);
		gint result = GTK_RESPONSE_YES;
		if (err) {
			char *unescaped = g_uri_unescape_string (filename, NULL);
			gchar * message = g_strdup_printf (_("File %s\nexists, overwrite?"), unescaped);
			g_free (unescaped);
			gcugtk::Message *box = new gcugtk::Message (static_cast < gcugtk::Application * > (App),
			                                            message, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, App->GetGtkWindow ());
			box->Run ();
			g_free (message);
		}
		if (result == GTK_RESPONSE_YES) {
			g_file_delete (file, NULL, NULL);
			char *fname = go_mime_to_image_format (mime_type);
			GOImageFormat format = go_image_get_format_from_name ((fname)? fname: filename);
			if (format == GO_IMAGE_FORMAT_UNKNOWN)
				return true;
			GError *error = NULL;
			GsfOutput *output = gsf_output_gio_new_for_uri (filename, &error);
			if (error) {
				g_error_free (error);
				return true;
			}
			GogGraph *gr = gog_graph_dup (graph);
			gog_graph_set_size (gr, GetImageWidth (), GetImageHeight ());
			gog_graph_export_image (gr, format, output, -1., -1.);
			g_object_unref (gr);

		}
		g_object_unref (file);
	}
	return false;
}
