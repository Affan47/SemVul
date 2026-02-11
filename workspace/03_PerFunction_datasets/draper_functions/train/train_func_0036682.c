mxl111sf_get_stream_config_mercury_mh(struct dvb_frontend *fe,
		u8 *ts_type, struct usb_data_stream_properties *stream)
{
	pr_debug("%s: fe=%d\n", __func__, fe->id);

	if (fe->id == 0) {
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		if (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 4, 96, 564);
		else
			mxl111sf_stream_config_bulk(stream, 4);
	} else if (fe->id == 1 && dvb_usb_mxl111sf_spi) {
		*ts_type = DVB_USB_FE_TS_TYPE_RAW;
		if (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 5, 96, 200);
		else
			mxl111sf_stream_config_bulk(stream, 5);
	} else if (fe->id == 1 && !dvb_usb_mxl111sf_spi) {
		*ts_type = DVB_USB_FE_TS_TYPE_RAW;
		if (dvb_usb_mxl111sf_isoc)
			mxl111sf_stream_config_isoc(stream, 6, 24, 3072);
		else
			mxl111sf_stream_config_bulk(stream, 6);
	}
	return 0;
}
