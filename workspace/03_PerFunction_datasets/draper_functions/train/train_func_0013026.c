parse_type(const char *value, query_t *query)
{
	uint16_t rtype;
	uint32_t serial;

	if (params_parse_type(value, &rtype, &serial) != KNOT_EOK) {
		return KNOT_EINVAL;
	}

	query->type_num = rtype;
	query->xfr_serial = serial;

	return KNOT_EOK;
}
