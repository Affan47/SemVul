add_ip_list_range(char* range, ip_range_list_t * list)
{
	char* separator = strchr(range, '-');

	if (separator) {
		*separator = '\0';
	}

	ioa_addr min, max;

	if (make_ioa_addr((const u08bits*) range, 0, &min) < 0) {
		TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Wrong address format: %s\n", range);
		return -1;
	}

	if (separator) {
		if (make_ioa_addr((const u08bits*) separator + 1, 0, &max) < 0) {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR, "Wrong address format: %s\n", separator + 1);
			return -1;
		}
	} else {

		addr_cpy(&max, &min);
	}

	if (separator)
		*separator = '-';

	++(list->ranges_number);
	list->ranges = (char**) turn_realloc(list->ranges, 0, sizeof(char*) * list->ranges_number);
	list->ranges[list->ranges_number - 1] = turn_strdup(range);
	list->encaddrsranges = (ioa_addr_range**) turn_realloc(list->encaddrsranges, 0, sizeof(ioa_addr_range*) * list->ranges_number);

	list->encaddrsranges[list->ranges_number - 1] = (ioa_addr_range*) turn_malloc(sizeof(ioa_addr_range));

	ioa_addr_range_set(list->encaddrsranges[list->ranges_number - 1], &min, &max);

	return 0;
}
