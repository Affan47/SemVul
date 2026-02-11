camel_session_ref_service_by_url (CamelSession *session,
                                  CamelURL *url,
                                  CamelProviderType type)
{
	CamelService *match = NULL;
	GList *list, *iter;

	g_return_val_if_fail (CAMEL_IS_SESSION (session), NULL);
	g_return_val_if_fail (url != NULL, NULL);

	list = camel_session_list_services (session);

	for (iter = list; iter != NULL; iter = g_list_next (iter)) {
		CamelProvider *provider;
		CamelService *service;
		CamelURL *service_url;
		gboolean url_equal;

		service = CAMEL_SERVICE (iter->data);
		provider = camel_service_get_provider (service);

		if (provider == NULL)
			continue;

		if (provider->url_equal == NULL)
			continue;

		service_url = camel_service_new_camel_url (service);
		url_equal = provider->url_equal (url, service_url);
		camel_url_free (service_url);

		if (!url_equal)
			continue;

		switch (type) {
			case CAMEL_PROVIDER_STORE:
				if (CAMEL_IS_STORE (service))
					match = g_object_ref (service);
				break;
			case CAMEL_PROVIDER_TRANSPORT:
				if (CAMEL_IS_TRANSPORT (service))
					match = g_object_ref (service);
				break;
			default:
				g_warn_if_reached ();
				break;
		}

		if (match != NULL)
			break;
	}

	g_list_free_full (list, (GDestroyNotify) g_object_unref);

	return match;
}
