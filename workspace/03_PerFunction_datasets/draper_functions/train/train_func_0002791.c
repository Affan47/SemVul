set_gemalto_firmware_features(unsigned int reader_index)
{
	_ccid_descriptor *ccid_descriptor = get_ccid_descriptor(reader_index);
	struct GEMALTO_FIRMWARE_FEATURES *gf_features;

	gf_features = malloc(sizeof(struct GEMALTO_FIRMWARE_FEATURES));
	if (gf_features)
	{
		unsigned char cmd[] = { 0x6A };
		unsigned int len_features = sizeof *gf_features;
		RESPONSECODE ret;

		ret = CmdEscape(reader_index, cmd, sizeof cmd,
			(unsigned char*)gf_features, &len_features, 0);
		if ((IFD_SUCCESS == ret) &&
		    (len_features == sizeof *gf_features))
		{


			ccid_descriptor->gemalto_firmware_features = gf_features;
#ifndef NO_LOG
			dump_gemalto_firmware_features(gf_features);
#endif
		}
		else
		{

			free(gf_features);
			DEBUG_INFO3("GET_FIRMWARE_FEATURES failed: " DWORD_D ", len=%d",
				ret, len_features);
		}
	}
}
