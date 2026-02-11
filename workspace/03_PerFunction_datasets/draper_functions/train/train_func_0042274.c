charset_generate_all(struct list_main **lists, char *charset)
{
	FILE *file;
	int was_error;
	struct charset_header *header;
	char_counters chars;
	crack_counters cracks;

	header = (struct charset_header *)mem_alloc(sizeof(*header));
	memset(header, 0, sizeof(*header));

	chars = (char_counters)mem_alloc(sizeof(*chars));
	cracks = (crack_counters)mem_alloc(sizeof(*cracks));

	if (!(file = fopen(path_expand(charset), "wb")))
		pexit("fopen: %s", path_expand(charset));

	charset_write_header(file, header);

	printf("Generating charsets");
	fflush(stdout);

	charset_generate_chars(lists, file, header, chars, cracks);
	if (event_abort) {
		fclose(file);
		unlink(charset);
		putchar('\n'); check_abort(0);
	}

	printf(" DONE\nGenerating cracking order");
	fflush(stdout);

	charset_generate_order(cracks, header->order, sizeof(header->order));
	if (event_abort) {
		fclose(file);
		unlink(charset);
		putchar('\n'); check_abort(0);
	}

	fflush(file);
	if (!ferror(file) && !fseek(file, 0, SEEK_SET)) {
		strncpy(header->version, CHARSET_V, sizeof(header->version));
		header->min = CHARSET_MIN;
		header->max = CHARSET_MAX;
		header->length = CHARSET_LENGTH;
		charset_checksum_header(header);
		charset_write_header(file, header);
	}

	MEM_FREE(cracks);
	MEM_FREE(chars);

	was_error = ferror(file);
	if (fclose(file) || was_error) {
		unlink(charset);
		fprintf(stderr, "Failed to write charset file: %s\n", charset);
		error();
	}

	printf("Successfully wrote charset file: %s (%d character%s)\n",
		charset, header->count, header->count != 1 ? "s" : "");

	MEM_FREE(header);
}
