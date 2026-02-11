geoclue_networkmanager_init (GeoclueNetworkManager *self)
{
	self->status = GEOCLUE_CONNECTIVITY_UNKNOWN;
	self->client = nm_client_new ();
	if (self->client == NULL) {
		g_warning ("%s was unable to create a connection to NetworkManager",
			   G_OBJECT_TYPE_NAME (self));
		return;
	}

	g_signal_connect (G_OBJECT (self->client), "notify::running",
	                  G_CALLBACK (nm_update_status_cb), self);
	g_signal_connect (G_OBJECT (self->client), "notify::state",
	                  G_CALLBACK (nm_update_status_cb), self);


	update_status (self, FALSE);
}
