search_mapserver(const char *map)
{
	int i, j;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		if (server_fd[i] < 0)
			continue;
		for(j = 0; j < server[i].map_num; j++) {
			if (!strncmp(server[i].map + (j * 16), map, 16))
				return i;
		}
	}

	return -1;
}
