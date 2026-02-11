_gdata_access_handler_get_rules (GDataAccessHandler *self, GDataService *service, GCancellable *cancellable,
                                 GDataQueryProgressCallback progress_callback, gpointer progress_user_data, gboolean is_async, GError **error)
{
	GDataAccessHandlerIface *iface;
	GDataAuthorizationDomain *domain = NULL;
	GDataFeed *feed;
	GDataLink *_link;
	SoupMessage *message;

	_link = gdata_entry_look_up_link (GDATA_ENTRY (self), GDATA_LINK_ACCESS_CONTROL_LIST);
	g_assert (_link != NULL);

	iface = GDATA_ACCESS_HANDLER_GET_IFACE (self);
	if (iface->get_authorization_domain != NULL) {
		domain = iface->get_authorization_domain (self);
	}

	message = _gdata_service_query (service, domain, gdata_link_get_uri (_link), NULL, cancellable, error);
	if (message == NULL) {
		return NULL;
	}

	g_assert (message->response_body->data != NULL);
	feed = _gdata_feed_new_from_xml (GDATA_TYPE_FEED, message->response_body->data, message->response_body->length, GDATA_TYPE_ACCESS_RULE,
	                                 progress_callback, progress_user_data, is_async, error);
	g_object_unref (message);

	return feed;
}
