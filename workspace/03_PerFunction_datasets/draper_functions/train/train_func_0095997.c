rdp_read_remote_programs_capability_set(STREAM* s, rdpSettings* settings)
{
	uint32 railSupportLevel;

	stream_read_uint32(s, railSupportLevel);

	if ((railSupportLevel & RAIL_LEVEL_SUPPORTED) == 0)
	{
		if (settings->remote_app == True)
		{

			settings->remote_app = False;
		}
	}
}
