metadata_value_free(gpointer data)
{
	struct metadata_value *value = data;

	switch (value->type) {
	case DBUS_TYPE_STRING:
		g_free(value->value.str);
		break;
	}

	g_free(value);
}
