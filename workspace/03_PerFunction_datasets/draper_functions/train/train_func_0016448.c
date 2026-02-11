imapx_settings_get_property (GObject *object,
                             guint property_id,
                             GValue *value,
                             GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_AUTH_MECHANISM:
			g_value_take_string (
				value,
				camel_network_settings_dup_auth_mechanism (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_BATCH_FETCH_COUNT:
			g_value_set_uint (
				value,
				camel_imapx_settings_get_batch_fetch_count (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_CHECK_ALL:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_check_all (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_CHECK_SUBSCRIBED:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_check_subscribed (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_FETCH_ORDER:
			g_value_set_enum (
				value,
				camel_imapx_settings_get_fetch_order (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_FILTER_ALL:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_filter_all (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_FILTER_JUNK:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_filter_junk (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_FILTER_JUNK_INBOX:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_filter_junk_inbox (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_HOST:
			g_value_take_string (
				value,
				camel_network_settings_dup_host (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_MOBILE_MODE:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_mobile_mode (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_NAMESPACE:
			g_value_take_string (
				value,
				camel_imapx_settings_dup_namespace (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_PORT:
			g_value_set_uint (
				value,
				camel_network_settings_get_port (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_REAL_JUNK_PATH:
			g_value_take_string (
				value,
				camel_imapx_settings_dup_real_junk_path (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_REAL_TRASH_PATH:
			g_value_take_string (
				value,
				camel_imapx_settings_dup_real_trash_path (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_SECURITY_METHOD:
			g_value_set_enum (
				value,
				camel_network_settings_get_security_method (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_SHELL_COMMAND:
			g_value_take_string (
				value,
				camel_imapx_settings_dup_shell_command (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_USER:
			g_value_take_string (
				value,
				camel_network_settings_dup_user (
				CAMEL_NETWORK_SETTINGS (object)));
			return;

		case PROP_USE_IDLE:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_use_idle (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_USE_NAMESPACE:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_use_namespace (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_USE_QRESYNC:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_use_qresync (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_USE_REAL_JUNK_PATH:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_use_real_junk_path (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_USE_REAL_TRASH_PATH:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_use_real_trash_path (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_USE_SHELL_COMMAND:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_use_shell_command (
				CAMEL_IMAPX_SETTINGS (object)));
			return;

		case PROP_USE_SUBSCRIPTIONS:
			g_value_set_boolean (
				value,
				camel_imapx_settings_get_use_subscriptions (
				CAMEL_IMAPX_SETTINGS (object)));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
