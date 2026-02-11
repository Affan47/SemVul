migrate_parse_weather_property (ParseData *parse_data,
                                const gchar *property_name,
                                const gchar *property_value)
{

	if (g_strcmp0 (property_name, "temperature") == 0) {
		gboolean metric;

		metric = (g_strcmp0 (property_value, "fahrenheit") != 0);

		g_key_file_set_string (
			parse_data->key_file,
			E_SOURCE_EXTENSION_WEATHER_BACKEND,
			"Units", metric ? "metric" : "imperial");

	} else if (g_strcmp0 (property_name, "units") == 0) {
		gboolean metric;

		metric = (g_strcmp0 (property_value, "metric") == 0);

		g_key_file_set_string (
			parse_data->key_file,
			E_SOURCE_EXTENSION_WEATHER_BACKEND,
			"Units", metric ? "metric" : "imperial");
	}
}
