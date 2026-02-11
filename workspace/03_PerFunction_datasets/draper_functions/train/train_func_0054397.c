server_side_source_set_property (GObject *object,
                                 guint property_id,
                                 const GValue *value,
                                 GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_ALLOW_AUTH_PROMPT:
			e_server_side_source_set_allow_auth_prompt (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_boolean (value));
			return;

		case PROP_AUTH_SESSION_TYPE:
			e_server_side_source_set_auth_session_type (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_gtype (value));
			return;

		case PROP_FILE:
			server_side_source_set_file (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_object (value));
			return;

		case PROP_OAUTH2_SUPPORT:
			e_server_side_source_set_oauth2_support (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_object (value));
			return;

		case PROP_REMOTE_CREATABLE:
			e_server_side_source_set_remote_creatable (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_boolean (value));
			return;

		case PROP_REMOTE_DELETABLE:
			e_server_side_source_set_remote_deletable (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_boolean (value));
			return;

		case PROP_REMOVABLE:
			e_server_side_source_set_removable (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_boolean (value));
			return;

		case PROP_SERVER:
			server_side_source_set_server (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_object (value));
			return;

		case PROP_WRITABLE:
			e_server_side_source_set_writable (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_boolean (value));
			return;

		case PROP_WRITE_DIRECTORY:
			e_server_side_source_set_write_directory (
				E_SERVER_SIDE_SOURCE (object),
				g_value_get_string (value));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
