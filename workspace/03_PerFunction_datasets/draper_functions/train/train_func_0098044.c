gdata_mock_server_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
	GDataMockServer *self = GDATA_MOCK_SERVER (object);

	switch (property_id) {
		case PROP_TRACE_DIRECTORY:
			gdata_mock_server_set_trace_directory (self, g_value_get_object (value));
			break;
		case PROP_ENABLE_ONLINE:
			gdata_mock_server_set_enable_online (self, g_value_get_boolean (value));
			break;
		case PROP_ENABLE_LOGGING:
			gdata_mock_server_set_enable_logging (self, g_value_get_boolean (value));
			break;
		case PROP_ADDRESS:
		case PROP_PORT:
		case PROP_RESOLVER:

		default:

			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
