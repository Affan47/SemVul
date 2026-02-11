xmms_pulse_flush (xmms_output_t *output)
{
	xmms_pulse_data_t *data;

	g_return_if_fail (output);
	data = xmms_output_private_data_get (output);
	g_return_if_fail (data);

	if (data->pulse)
		xmms_pulse_backend_flush (data->pulse, NULL);
}
