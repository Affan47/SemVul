read_node(FILE *f)
{
	char buffer[256];
	struct string_list node = {
		.string = buffer,
		.tag = SYM_NORMAL };
	int c, in_string = 0;

	while ((c = fgetc(f)) != EOF) {
		if (!in_string && c == ' ') {
			if (node.string == buffer)
				continue;
			break;
		} else if (c == '"') {
			in_string = !in_string;
		} else if (c == '\n') {
			if (node.string == buffer)
				return NULL;
			ungetc(c, f);
			break;
		}
		if (node.string >= buffer + sizeof(buffer) - 1) {
			fprintf(stderr, "Token too long\n");
			exit(1);
		}
		*node.string++ = c;
	}
	if (node.string == buffer)
		return NULL;
	*node.string = 0;
	node.string = buffer;

	if (node.string[1] == '#') {
		size_t n;

		for (n = 0; n < ARRAY_SIZE(symbol_types); n++) {
			if (node.string[0] == symbol_types[n].n) {
				node.tag = n;
				node.string += 2;
				return copy_node(&node);
			}
		}
		fprintf(stderr, "Unknown type %c\n", node.string[0]);
		exit(1);
	}
	return copy_node(&node);
}
