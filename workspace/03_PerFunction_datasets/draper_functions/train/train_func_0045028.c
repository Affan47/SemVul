gdip_get_imageformat_from_codec_clsid (CLSID *encoderCLSID)
{
	GpStatus status;
	UINT numEncoders, size, cnt;
    	ImageCodecInfo *encoders, *encoder;

	status = GdipGetImageEncodersSize (&numEncoders, &size);
	if ((status != Ok) ||(numEncoders == 0))
		return INVALID;

    	encoders = GdipAlloc (size);

	status = GdipGetImageEncoders (numEncoders, size, encoders);
	if (status != Ok)
		return INVALID;

    	for (cnt = 0, encoder = encoders; cnt < numEncoders; cnt++, encoder++) {
	       	if (memcmp (&encoder->Clsid, encoderCLSID, sizeof (GUID)) == 0) {
			ImageFormat ifmt = gdip_image_format_for_format_guid (&encoder->FormatID);
            		GdipFree (encoders);
			return ifmt;
        	}
    	}

    	GdipFree (encoders);
    	return INVALID;
}
