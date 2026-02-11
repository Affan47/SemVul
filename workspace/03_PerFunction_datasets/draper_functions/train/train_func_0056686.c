ISOR_CloseService(GF_InputService *plug)
{
	GF_Err reply;
	ISOMReader *read;
	if (!plug || !plug->priv) return GF_SERVICE_ERROR;
	read = (ISOMReader *) plug->priv;
	reply = GF_OK;

	if (read->mov) gf_isom_close(read->mov);
	read->mov = NULL;

	while (gf_list_count(read->channels)) {
		ISOMChannel *ch = (ISOMChannel *)gf_list_get(read->channels, 0);
		gf_list_rem(read->channels, 0);
		isor_delete_channel(read, ch);
	}

	if (read->dnload) gf_term_download_del(read->dnload);
	read->dnload = NULL;

	gf_term_on_disconnect(read->service, NULL, reply);
	return GF_OK;
}
