bg_configure_ba_passthroughs_string(uint16_t passthrough)
{
	if (bg_configure_init() < 0)
		return NULL;

	return (*(ops.ba_passthroughs_string))
		(passthrough);
}
