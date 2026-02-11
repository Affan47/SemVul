soi_cb_save_as (SheetObject *so, SheetControl *sc)
{
	WBCGtk *wbcg;
	char *uri;
	GsfOutput *output;
	GSList *l = NULL;
	GOImageFormat sel_fmt;
	GOImageFormatInfo const *format_info;
	GdkPixbuf *pixbuf = NULL;
	GError *err = NULL;
	SheetObjectImage *soi = SHEET_OBJECT_IMAGE (so);

	g_return_if_fail (soi != NULL);

	sel_fmt  = go_image_get_format_from_name (soi->type);
	if ((pixbuf = go_image_get_pixbuf (soi->image)) != NULL)
		l = go_image_get_formats_with_pixbuf_saver ();

	if (sel_fmt != GO_IMAGE_FORMAT_UNKNOWN) {
		l = g_slist_remove (l, GUINT_TO_POINTER (sel_fmt));
		l = g_slist_prepend (l, GUINT_TO_POINTER (sel_fmt));
	}

	wbcg = scg_wbcg (SHEET_CONTROL_GUI (sc));

	uri = go_gui_get_image_save_info (wbcg_toplevel (wbcg), l, &sel_fmt, NULL);
	if (!uri)
		goto out;

	output = go_file_create (uri, &err);
	if (!output)
		goto out;
	format_info = go_image_get_format_info (sel_fmt);
	sheet_object_write_image (so, (format_info? format_info->name: NULL), -1.0, output, &err);
	gsf_output_close (output);
	g_object_unref (output);

	if (err != NULL)
		go_cmd_context_error (GO_CMD_CONTEXT (wbcg), err);

out:
	if (pixbuf)
		g_object_unref (pixbuf);
	g_free (uri);
	g_slist_free (l);
}
