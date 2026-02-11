soup_requester_add_feature (SoupSessionFeature *feature, GType type)
{
	SoupRequester *requester = SOUP_REQUESTER (feature);

	if (!g_type_is_a (type, SOUP_TYPE_REQUEST))
		return FALSE;

	soup_session_add_feature_by_type (requester->priv->session, type);
	return TRUE;
}
