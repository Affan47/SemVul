xmms_pulse_format_set (xmms_output_t *output, const xmms_stream_type_t *format)
{
	xmms_pulse_data_t *data;
	const xmms_config_property_t *val;
	const gchar *sink, *name;
	xmms_sample_format_t xmms_format;
	gint channels;
	gint samplerate;

	g_return_val_if_fail (output, FALSE);
	data = xmms_output_private_data_get (output);
	g_return_val_if_fail (data, FALSE);

	xmms_format = xmms_stream_type_get_int (format,
	                                        XMMS_STREAM_TYPE_FMT_FORMAT);
	channels = xmms_stream_type_get_int (format,
	                                     XMMS_STREAM_TYPE_FMT_CHANNELS);
	samplerate = xmms_stream_type_get_int (format,
	                                       XMMS_STREAM_TYPE_FMT_SAMPLERATE);

	val = xmms_output_config_lookup (output, "sink");
	sink = xmms_config_property_get_string (val);
	if (sink && *sink == '\0')
		sink = NULL;

	val = xmms_output_config_lookup (output, "name");
	name = xmms_config_property_get_string (val);
	if (!name || *name == '\0')
		name = XMMS_PULSE_DEFAULT_NAME;

	if (!xmms_pulse_backend_set_stream (data->pulse, name, sink, xmms_format,
	                                    samplerate, channels, NULL))
		return FALSE;

	return TRUE;
}
