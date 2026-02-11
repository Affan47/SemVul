read_map(const char *filename)
{
	const int HASH_SIZE = 1000;

	FILE *map_file = fopen(filename, "r");
	if (NULL == map_file) { perror(NULL); exit(EXIT_FAILURE); }

	struct hash *map = create_hash(HASH_SIZE);
	if (NULL == map) { perror(NULL); exit(EXIT_FAILURE); }

	char *line;
	while (NULL != (line = read_line(map_file))) {

		if ('#' == line[0] || is_all_whitespace(line)) {
			free(line);
			continue;
		}

		char *key, *value;
		struct word_tokenizer *wtok = create_word_tokenizer(line);
		if (NULL == wtok) { perror(NULL); exit(EXIT_FAILURE); }
		key = wt_next(wtok);
		if (NULL == key) {
			fprintf (stderr,
				"Wrong format in line '%s' - aborting.\n",
				line);
			exit(EXIT_FAILURE);
		}
		value = wt_next(wtok);
		if (NULL == value) {


			value = strdup("");
		}
		if (! hash_set(map, key, (void *) value)) {
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		destroy_word_tokenizer(wtok);
		free(key);
		free(line);
	}

	return map;
}
