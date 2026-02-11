gzip_flush (GsfOutputGZip *gzip)
{
	int zret;

	do {
		zret = deflate (&gzip->stream, Z_FINISH);
		if (zret == Z_OK) {


			if (!gzip_output_block (gzip))
				return FALSE;
		}
	} while (zret == Z_OK);
	if (zret != Z_STREAM_END) {
		gsf_output_set_error (GSF_OUTPUT (gzip), 0,
				      "Unexpected compression failure");
		g_warning ("Unexpected error code %d from zlib during compression.",
			   zret);
		return FALSE;
	}
	if (!gzip_output_block (gzip))
		return FALSE;

	return TRUE;
}
