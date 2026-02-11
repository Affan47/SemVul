jack_internal_client_handle (jack_client_t *client,
			     const char *client_name,
			     jack_status_t *status)
{
	jack_request_t req;
	jack_status_t my_status;

	if (status == NULL)
		status = &my_status;
	*status = 0;

	memset (&req, 0, sizeof (req));
	req.type = IntClientHandle;
	req.x.intclient.options = JackNullOption;
	strncpy (req.x.intclient.name, client_name,
		 sizeof (req.x.intclient.name));

	*status = jack_client_deliver_request (client, &req);

	return req.x.intclient.id;
}
