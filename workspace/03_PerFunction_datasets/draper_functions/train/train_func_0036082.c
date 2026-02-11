get_proc_maps(unsigned int *num)
{
	char *buf, *p;
	struct ptr_valid_map *map;
	unsigned int max = 16;

	buf = grab("/proc/self/maps");
	if (!buf) {
		*num = 0;
		return NULL;
	}

	map = malloc(sizeof(*map) * max);
	if (!map)
		goto free_buf;

	*num = 0;
	for (p = buf; p && *p; p = skip_line(p)) {
		unsigned long start, end;
		char *endp;


		start = strtoul(p, &endp, 16);
		if (*endp != '-')
			goto malformed;
		end = strtoul(endp+1, &endp, 16);
		if (*endp != ' ')
			goto malformed;

		endp++;
		if (endp[0] != 'r' && endp[0] != '-')
			goto malformed;
		if (endp[1] != 'w' && endp[1] != '-')
			goto malformed;


		if (endp[0] == 'r') {
			map = add_map(map, num, &max, start, end,
				      endp[1] == 'w');
			if (!map)
				goto free_buf;
		}
	}

	free(buf);
	return map;


malformed:
	free(map);
free_buf:
	free(buf);
	*num = 0;
	return NULL;
}
