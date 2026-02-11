decode_waypoints(level *loadlevel, char *data)
{
	char *wp_begin, *wp_end;
	char *this_line;
	int nr, x, y, wp_rnd;
	char *pos;


	dynarray_init(&loadlevel->waypoints, 2, sizeof(struct waypoint));

	if (loadlevel->random_dungeon && !loadlevel->dungeon_generated)
		return data;


	if ((wp_begin = strstr(data, WP_BEGIN_STRING)) == NULL)
		return NULL;
	wp_begin += strlen(WP_BEGIN_STRING) + 1;

	if ((wp_end = strstr(data, WP_END_STRING)) == NULL)
		return NULL;

	int curlinepos = 0;
	this_line = (char *)MyMalloc(4096);

	while (1) {

		short int nlpos = 0;
		memset(this_line, 0, 4096);
		while (wp_begin[curlinepos + nlpos] != '\n')
			nlpos++;
		memcpy(this_line, wp_begin + curlinepos, nlpos);
		this_line[nlpos] = '\0';
		nlpos++;

		curlinepos += nlpos;

		if (!strncmp(this_line, wp_end, strlen(WP_END_STRING))) {
			break;
		}
		wp_rnd = 0;
		sscanf(this_line, "Nr.=%d \t x=%d \t y=%d   rnd=%d", &nr, &x, &y, &wp_rnd);


		waypoint new_wp;
		new_wp.x = x;
		new_wp.y = y;
		new_wp.suppress_random_spawn = wp_rnd;


		dynarray_init(&new_wp.connections, 2, sizeof(int));

		pos = strstr(this_line, CONNECTION_STRING);
		if (pos == NULL) {
			fprintf(stderr, "Unable to find connection string. line is %s, level %i\n", this_line,
				loadlevel->levelnum);
		}
		pos += strlen(CONNECTION_STRING);
		pos += strspn(pos, WHITE_SPACE);

		while (1) {
			if (*pos == '\0')
				break;
			int connection;
			int res = sscanf(pos, "%d", &connection);
			if ((connection == -1) || (res == 0) || (res == EOF))
				break;


			dynarray_add(&new_wp.connections, &connection, sizeof(int));

			pos += strcspn(pos, WHITE_SPACE);
			pos += strspn(pos, WHITE_SPACE);
		}


		dynarray_add(&loadlevel->waypoints, &new_wp, sizeof(struct waypoint));
	}

	free(this_line);
	return wp_end;
}
