shearwater_predator_parser_get_field (dc_parser_t *abstract, dc_field_type_t type, unsigned int flags, void *value)
{
	shearwater_predator_parser_t *parser = (shearwater_predator_parser_t *) abstract;

	const unsigned char *data = abstract->data;
	unsigned int size = abstract->size;

	if (size < 2 * SZ_BLOCK)
		return DC_STATUS_DATAFORMAT;


	unsigned int footer = size - SZ_BLOCK;
	if (parser->petrel || array_uint16_be (data + footer) == 0xFFFD) {
		if (size < 3 * SZ_BLOCK)
			return DC_STATUS_DATAFORMAT;

		footer -= SZ_BLOCK;
	}


	unsigned int units = data[8];

	dc_gasmix_t *gasmix = (dc_gasmix_t *) value;
	dc_salinity_t *water = (dc_salinity_t *) value;
	unsigned int density = 0;

	if (value) {
		switch (type) {
		case DC_FIELD_DIVETIME:
			*((unsigned int *) value) = array_uint16_be (data + footer + 6) * 60;
			break;
		case DC_FIELD_MAXDEPTH:
			if (units == IMPERIAL)
				*((double *) value) = array_uint16_be (data + footer + 4) * FEET;
			else
				*((double *) value) = array_uint16_be (data + footer + 4);
			break;
		case DC_FIELD_GASMIX_COUNT:
			*((unsigned int *) value) = 10;
			break;
		case DC_FIELD_GASMIX:
			gasmix->oxygen = data[20 + flags] / 100.0;
			gasmix->helium = data[30 + flags] / 100.0;
			gasmix->nitrogen = 1.0 - gasmix->oxygen - gasmix->helium;
			break;
		case DC_FIELD_SALINITY:
			density = array_uint16_be (data + 83);
			if (density == 1000)
				water->type = DC_WATER_FRESH;
			else
				water->type = DC_WATER_SALT;
			water->density = density;
			break;
		case DC_FIELD_ATMOSPHERIC:
			*((double *) value) = array_uint16_be (data + 47) / 1000.0;
			break;
		default:
			return DC_STATUS_UNSUPPORTED;
		}
	}

	return DC_STATUS_SUCCESS;
}
