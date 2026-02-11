DIM_ServiceChannel(struct dim_channel *ch)
{
	if (!g.dim_is_initialized || !ch)
		return DIM_ERR_DRIVER_NOT_INITIALIZED;

	return channel_service(ch);
}
