facebook_service_get_user_info_ready_cb (SoupSession *session,
				         SoupMessage *msg,
				         gpointer     user_data)
{
	FacebookService    *self = user_data;
	GSimpleAsyncResult *result;
	GError             *error = NULL;
	JsonNode           *node;

	result = _web_service_get_result (WEB_SERVICE (self));

	if (facebook_utils_parse_response (msg, &node, &error)) {
		OAuthAccount *account;

		account = (OAuthAccount *) json_gobject_deserialize (OAUTH_TYPE_ACCOUNT, node);
		g_object_set (account,
			      "token", _facebook_service_get_access_token (self),
			      "token-secret", _facebook_service_get_access_token (self),
			      NULL);
		g_simple_async_result_set_op_res_gpointer (result,
							   g_object_ref (account),
							   (GDestroyNotify) g_object_unref);

		_g_object_unref (account);
		json_node_free (node);
	}
	else
		g_simple_async_result_set_from_error (result, error);

	g_simple_async_result_complete_in_idle (result);
}
