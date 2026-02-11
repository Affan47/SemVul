dft_read_modified(void)
{
	if (dft_savebuf_len) {
		trace_ds("> WriteStructuredField FileTransferData\n");
		obptr = obuf;
		space3270out(dft_savebuf_len);
		memcpy(obptr, dft_savebuf, dft_savebuf_len);
		obptr += dft_savebuf_len;
		net_output();
	}
}
