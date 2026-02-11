hw_ostc_parser_get_datetime (dc_parser_t *abstract, dc_datetime_t *datetime)
{
	hw_ostc_parser_t *parser = (hw_ostc_parser_t *) abstract;
	const unsigned char *data = abstract->data;
	unsigned int size = abstract->size;

	if (size < 9)
		return DC_STATUS_DATAFORMAT;


	unsigned int version = data[parser->frog ? 8 : 2];
	const hw_ostc_layout_t *layout = NULL;
	unsigned int header = 0;
	switch (version) {
	case 0x20:
		layout = &hw_ostc_layout_ostc;
		header = 47;
		break;
	case 0x21:
		layout = &hw_ostc_layout_ostc;
		header = 57;
		break;
	case 0x22:
		layout = &hw_ostc_layout_frog;
		header = 256;
		break;
	case 0x23:
		layout = &hw_ostc_layout_ostc3;
		header = 256;
		break;
	default:
		return DC_STATUS_DATAFORMAT;
	}

	if (size < header)
		return DC_STATUS_DATAFORMAT;

	unsigned int divetime = 0;
	if (version > 0x20) {


		divetime = (array_uint16_le (data + layout->duration) / 60) * 60;
	} else {

		divetime = array_uint16_le (data + layout->divetime) * 60 + data[layout->divetime + 2];
	}

	const unsigned char *p = data + layout->datetime;

	dc_datetime_t dt;
	if (version == 0x23) {
		dt.year   = p[0] + 2000;
		dt.month  = p[1];
		dt.day    = p[2];
	} else {
		dt.year   = p[2] + 2000;
		dt.month  = p[0];
		dt.day    = p[1];
	}
	dt.hour   = p[3];
	dt.minute = p[4];
	dt.second = 0;

	dc_ticks_t ticks = dc_datetime_mktime (&dt);
	if (ticks == (dc_ticks_t) -1)
		return DC_STATUS_DATAFORMAT;

	ticks -= divetime;

	if (!dc_datetime_localtime (datetime, ticks))
		return DC_STATUS_DATAFORMAT;

	return DC_STATUS_SUCCESS;
}
