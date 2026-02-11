oceanic_vtpro_parser_get_field (dc_parser_t *abstract, dc_field_type_t type, unsigned int flags, void *value)
{
	oceanic_vtpro_parser_t *parser = (oceanic_vtpro_parser_t *) abstract;

	const unsigned char *data = abstract->data;
	unsigned int size = abstract->size;

	if (size < 7 * PAGESIZE / 2)
		return DC_STATUS_DATAFORMAT;

	if (!parser->cached) {
		sample_statistics_t statistics = SAMPLE_STATISTICS_INITIALIZER;
		dc_status_t rc = oceanic_vtpro_parser_samples_foreach (
			abstract, sample_statistics_cb, &statistics);
		if (rc != DC_STATUS_SUCCESS)
			return rc;

		parser->cached = 1;
		parser->divetime = statistics.divetime;
		parser->maxdepth = statistics.maxdepth;
	}

	unsigned int footer = size - PAGESIZE;

	dc_gasmix_t *gasmix = (dc_gasmix_t *) value;

	if (value) {
		switch (type) {
		case DC_FIELD_DIVETIME:
			*((unsigned int *) value) = parser->divetime;
			break;
		case DC_FIELD_MAXDEPTH:
			*((double *) value) = (data[footer + 0] + ((data[footer + 1] & 0x0F) << 8)) * FEET;
			break;
		case DC_FIELD_GASMIX_COUNT:
			*((unsigned int *) value) = 1;
			break;
		case DC_FIELD_GASMIX:
			gasmix->helium = 0.0;
			if (data[footer + 3])
				gasmix->oxygen = data[footer + 3] / 100.0;
			else
				gasmix->oxygen = 0.21;
			gasmix->nitrogen = 1.0 - gasmix->oxygen - gasmix->helium;
			break;
		default:
			return DC_STATUS_UNSUPPORTED;
		}
	}

	return DC_STATUS_SUCCESS;
}
