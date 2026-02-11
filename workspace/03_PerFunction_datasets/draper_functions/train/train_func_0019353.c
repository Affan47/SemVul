test_oauth1_authorizer_constructor_for_domains (void)
{
	GDataOAuth1Authorizer *authorizer;
	GDataAuthorizationDomain *domain;
	GList *domains;


	domains = gdata_service_get_authorization_domains (GDATA_TYPE_CONTACTS_SERVICE);
	authorizer = gdata_oauth1_authorizer_new_for_authorization_domains ("Application name", domains);
	g_list_free (domains);

	g_assert (authorizer != NULL);
	g_assert (GDATA_IS_OAUTH1_AUTHORIZER (authorizer));
	g_assert (GDATA_IS_AUTHORIZER (authorizer));

	g_object_unref (authorizer);


	domain = GDATA_AUTHORIZATION_DOMAIN (g_object_new (GDATA_TYPE_AUTHORIZATION_DOMAIN,
	                                                   "service-name", "test",
	                                                   "scope", "test",
	                                                   NULL));

	domains = g_list_prepend (NULL, domain);
	authorizer = gdata_oauth1_authorizer_new_for_authorization_domains ("Application name", domains);
	g_list_free (domains);

	g_assert (authorizer != NULL);
	g_assert (GDATA_IS_OAUTH1_AUTHORIZER (authorizer));
	g_assert (GDATA_IS_AUTHORIZER (authorizer));

	g_object_unref (authorizer);
	g_object_unref (domain);
}
