read_int_hash_map_node_tp(FILE *fh, int_hash_map_node_t **foo, char *lastval, int *line, int *hiteof)
{
	static char buffer[80];

	if (lastval[0] == '\\') {
		*foo = NULL;
	} else {
		*foo = (int_hash_map_node_t*)malloc(sizeof(int_hash_map_node_t));
		if (lastval[0] != '[')
		{
			sciprintf("Expected opening bracket in hash_map_node_t on line %d\n", *line);
			return 1;
		}

		do {
			(*line)++;
			fgets(buffer, 80, fh);
			if (buffer[0] == 'L')
			{
				(*foo)->next = NULL;
				buffer[0] = buffer[1];
			}
			if (buffer[0] == ']')
			{
				break;
			}
			else if (buffer[0] == '[')
			{
				if (read_int_hash_map_node_tp(fh, &((*foo)->next), buffer, line, hiteof))
					return 1;
			}
			else if (sscanf(buffer, "%d=>%d", &((*foo)->name), &((*foo)->value))<2)
			{
				sciprintf("Error parsing hash_map_node_t on line %d\n", *line);
				return 1;
			}
		} while (1);
	}

	return 0;
}
