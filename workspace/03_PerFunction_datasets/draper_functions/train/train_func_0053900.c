read_response(FILE * fd) {
	unsigned size = 512, index = 0;
	char * content = malloc(size * sizeof(char));

	debug("read unchunked\n");

	while(!feof(fd)) {
		int c = fgetc(fd);

		if(c == EOF) {
			break;
		}
		else {
			content[index++] = c;

			if(index == (size - 2)) {
				size += 512;
				content = realloc(content, size * sizeof(char));
			}
		}
	}

	content = realloc(content, (index + 1) * sizeof(char));
	content[index] = 0;

	debug("result (%d): <\n%s\n>\n", index + 1, content);

	return content;
}
