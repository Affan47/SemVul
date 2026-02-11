get_mapping_weight(struct dundi_mapping *map, struct varshead *headp)
{
	char buf[32];

	buf[0] = 0;
	if (map->weightstr) {
		if (headp) {
			pbx_substitute_variables_varshead(headp, map->weightstr, buf, sizeof(buf) - 1);
		} else {
			pbx_substitute_variables_helper(NULL, map->weightstr, buf, sizeof(buf) - 1);
		}

		if (sscanf(buf, "%30d", &map->_weight) != 1)
			map->_weight = MAX_WEIGHT;
	}

	return map->_weight;
}
