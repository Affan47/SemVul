xmms_oss_flush (xmms_output_t *output)
{
	xmms_oss_data_t *data;

	g_return_if_fail (output);
	data = xmms_output_private_data_get (output);
	g_return_if_fail (data);


	ioctl (data->fd, SNDCTL_DSP_RESET, 0);

}
