disco_store_constructed (GObject *object)
{
	CamelDiscoStore *disco;
	CamelService *service;
	CamelSession *session;

	disco = CAMEL_DISCO_STORE (object);


	G_OBJECT_CLASS (camel_disco_store_parent_class)->constructed (object);

	service = CAMEL_SERVICE (object);
	session = camel_service_ref_session (service);

	if (camel_session_get_online (session))
		disco->status = CAMEL_DISCO_STORE_ONLINE;
	else
		disco->status = CAMEL_DISCO_STORE_OFFLINE;

	g_signal_connect (
		service, "notify::connection-status",
		G_CALLBACK (disco_store_update_status), NULL);

	g_object_unref (session);
}
