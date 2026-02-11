gsf_output_stdio_write (GsfOutput *output,
			size_t num_bytes,
			guint8 const *buffer)
{
	GsfOutputStdio *stdio = GSF_OUTPUT_STDIO (output);
	size_t written, remaining;

	g_return_val_if_fail (stdio != NULL, FALSE);
	g_return_val_if_fail (stdio->file != NULL, FALSE);

	remaining = num_bytes;

	while (remaining > 0) {
		written = fwrite (buffer + (num_bytes - remaining), 1,
				  remaining, stdio->file);
		if ((written < remaining) && ferror (stdio->file) != 0)
			return gsf_output_set_error (output, errno, "%s", g_strerror (errno));

		remaining -= written;
	}
	return TRUE;
}
