deleteHook (struct stream_data *data)
{
	if (data->flags & SF_SECURE) {
		iks_default_tls.terminate(data->tlsdata);
		data->tlsdata = NULL;
	}
	if (data->trans) data->trans->close (data->sock);
	data->trans = NULL;
	if (data->current) iks_delete (data->current);
	data->current = NULL;
	data->flags = 0;
}
