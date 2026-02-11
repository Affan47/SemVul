gsf_output_gzip_close (GsfOutput *output)
{
	if (!gsf_output_error (output)) {
		GsfOutputGZip *gzip = GSF_OUTPUT_GZIP (output);

		if (!gzip_flush (gzip))
			return FALSE;

		if (!gzip->raw) {
			guint8 buf[8];

			GSF_LE_SET_GUINT32 (buf,     gzip->crc);
			GSF_LE_SET_GUINT32 (buf + 4, gzip->isize);
			if (!gsf_output_write (gzip->sink, 8, buf))
				return FALSE;
		}
	}

	return TRUE;
}
