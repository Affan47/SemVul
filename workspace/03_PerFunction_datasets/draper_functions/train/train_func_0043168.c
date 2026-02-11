atomics_cobalt_parser_get_field (dc_parser_t *abstract, dc_field_type_t type, unsigned int flags, void *value)
{
	atomics_cobalt_parser_t *parser = (atomics_cobalt_parser_t *) abstract;

	if (abstract->size < SZ_HEADER)
		return DC_STATUS_DATAFORMAT;

	const unsigned char *p = abstract->data;

	dc_gasmix_t *gasmix = (dc_gasmix_t *) value;

	double atmospheric = 0.0;
	if (parser->atmospheric)
		atmospheric = parser->atmospheric;
	else
		atmospheric = array_uint16_le (p + 0x26) * BAR / 1000.0;

	if (value) {
		switch (type) {
		case DC_FIELD_DIVETIME:
			*((unsigned int *) value) = array_uint16_le (p + 0x58) * 60;
			break;
		case DC_FIELD_MAXDEPTH:
			*((double *) value) = (array_uint16_le (p + 0x56) * BAR / 1000.0 - atmospheric) / parser->hydrostatic;
			break;
		case DC_FIELD_GASMIX_COUNT:
			*((unsigned int *) value) = p[0x2a];
			break;
		case DC_FIELD_GASMIX:
			gasmix->helium = p[SZ_HEADER + SZ_GASMIX * flags + 5] / 100.0;
			gasmix->oxygen = p[SZ_HEADER + SZ_GASMIX * flags + 4] / 100.0;
			gasmix->nitrogen = 1.0 - gasmix->oxygen - gasmix->helium;
			break;
		default:
			return DC_STATUS_UNSUPPORTED;
		}
	}

	return DC_STATUS_SUCCESS;
}
