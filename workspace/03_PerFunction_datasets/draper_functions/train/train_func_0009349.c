IMG_CloseService(GF_InputService *plug)
{
	IMGLoader *read;
	if (!plug)
		return GF_BAD_PARAM;
	read = (IMGLoader *)plug->priv;
	if (!read)
		return GF_BAD_PARAM;
	if (read->stream) fclose(read->stream);
	read->stream = NULL;
	if (read->dnload) gf_term_download_del(read->dnload);
	read->dnload = NULL;
	if (read->service)
		gf_term_on_disconnect(read->service, NULL, GF_OK);
	return GF_OK;
}
