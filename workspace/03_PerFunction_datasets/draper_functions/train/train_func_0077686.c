decode_map(level *loadlevel, char *data)
{
	char *map_begin, *map_end;
	char *this_line;
	int i;

	if ((map_begin = strstr(data, MAP_BEGIN_STRING)) == NULL)
		return NULL;
	map_begin += strlen(MAP_BEGIN_STRING) + 1;

	if ((map_end = strstr(data, MAP_END_STRING)) == NULL)
		return NULL;


	unsigned int curlinepos = 0;
	this_line = (char *)MyMalloc(4096);


	for (i = 0; i < loadlevel->ylen; i++) {
		int col;
		int layer;
		map_tile *Buffer;
		int tmp;


		unsigned int nlpos = 0;
		memset(this_line, 0, 4096);
		while (map_begin[curlinepos + nlpos] != '\n')
			nlpos++;
		memcpy(this_line, map_begin + curlinepos, nlpos);
		this_line[nlpos] = '\0';
		nlpos++;


		Buffer = MyMalloc((loadlevel->xlen + 10) * sizeof(map_tile));
		for (col = 0; col < loadlevel->xlen; col++) {
			for (layer = 0; layer < loadlevel->floor_layers; layer++) {
				tmp = strtol(this_line + 4 * (loadlevel->floor_layers * col + layer), NULL, 10);
				Buffer[col].floor_values[layer] = (Uint16) tmp;
			}

			for ( ; layer < MAX_FLOOR_LAYERS; layer++)
				Buffer[col].floor_values[layer] = ISO_FLOOR_EMPTY;
			dynarray_init(&Buffer[col].glued_obstacles, 0, sizeof(int));
		}


		loadlevel->map[i] = Buffer;

		curlinepos += nlpos;
	}

	free(this_line);
	return map_end;
}
