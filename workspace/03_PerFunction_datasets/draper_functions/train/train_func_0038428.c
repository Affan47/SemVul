authentication_session_get_property (GObject *object,
                                     guint property_id,
                                     GValue *value,
                                     GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_AUTHENTICATOR:
			g_value_set_object (
				value,
				e_authentication_session_get_authenticator (
				E_AUTHENTICATION_SESSION (object)));
			return;

		case PROP_PROMPT_DESCRIPTION:
			g_value_take_string (
				value,
				e_authentication_session_dup_prompt_description (
				E_AUTHENTICATION_SESSION (object)));
			return;

		case PROP_PROMPT_MESSAGE:
			g_value_take_string (
				value,
				e_authentication_session_dup_prompt_message (
				E_AUTHENTICATION_SESSION (object)));
			return;

		case PROP_PROMPT_TITLE:
			g_value_take_string (
				value,
				e_authentication_session_dup_prompt_title (
				E_AUTHENTICATION_SESSION (object)));
			return;

		case PROP_SERVER:
			g_value_set_object (
				value,
				e_authentication_session_get_server (
				E_AUTHENTICATION_SESSION (object)));
			return;

		case PROP_SOURCE_UID:
			g_value_set_string (
				value,
				e_authentication_session_get_source_uid (
				E_AUTHENTICATION_SESSION (object)));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
