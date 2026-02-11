jack_set_sync_callback (jack_client_t *client,
			JackSyncCallback sync_callback, void *arg)
{
	jack_client_control_t *ctl = client->control;
	jack_request_t req;
	int rc;

        VALGRIND_MEMSET (&req, 0, sizeof (req));

	if (sync_callback)
		req.type = SetSyncClient;
	else
		req.type = ResetSyncClient;
	req.x.client_id = ctl->id;

	rc = jack_client_deliver_request (client, &req);
	if (rc == 0) {
		client->sync_cb = sync_callback;
		client->sync_arg = arg;
		ctl->sync_cb_cbset = TRUE;
	}
	return rc;
}
