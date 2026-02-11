SaveAsImage (string const &filename, char const *mime_type, unsigned width, unsigned height) const
{
	char *fname = go_mime_to_image_format (mime_type);
	GOImageFormat format = go_image_get_format_from_name ((fname)? fname: filename.c_str ());
	if (format == GO_IMAGE_FORMAT_UNKNOWN)
		return;
	GError *error = NULL;
	GsfOutput *output = gsf_output_gio_new_for_uri (filename.c_str (), &error);
	if (error) {
		g_error_free (error);
		return;
	}
	GogGraph *graph = gog_graph_dup (go_graph_widget_get_graph (GO_GRAPH_WIDGET (m_Widget)));
	gog_graph_set_size (graph, width, height);
	gog_graph_export_image (graph, format, output, -1., -1.);
	g_object_unref (graph);
}
