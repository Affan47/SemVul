gsf_input_gzip_finalize (GObject *obj)
{
	GsfInputGZip *gzip = (GsfInputGZip *)obj;

	gsf_input_gzip_set_source (gzip, NULL);

	g_free (gzip->buf);

	if (gzip->stream.state != NULL)
		inflateEnd (&(gzip->stream));

	g_clear_error (&gzip->err);

	parent_class->finalize (obj);
}
