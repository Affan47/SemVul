gsf_output_gio_close (GsfOutput *output)
{
	GsfOutputGio *gio = GSF_OUTPUT_GIO (output);

	if (gio->stream != NULL) {
		g_output_stream_close (gio->stream, NULL, NULL);
		g_object_unref (gio->stream);
		gio->stream = NULL;

		g_object_unref (gio->file);
		gio->file = NULL;

		return TRUE;
	}

	return FALSE;
}
