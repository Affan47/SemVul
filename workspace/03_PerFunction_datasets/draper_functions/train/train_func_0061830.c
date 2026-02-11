zReadFastaFile (FILE *stream, zFastaFile* entry){


	char c;
	char defline[4096];
	size_t buffer_size = 1024;
	size_t buffer_index;
	char *buffer;


	c = fgetc(stream);
	if (c == EOF) return 0;
	if (c != '>') {
		zWarn("zReadFastaFile > not found");
		return 0;
	}
	(void)ungetc(c, stream);


	(void)fgets(defline, sizeof(defline), stream);
	entry->def = zMalloc(strlen(defline) +1, "zReadFastaFile defline");
	(void)strcpy(entry->def, defline);
	entry->def[strlen(entry->def) -1] = '\0';


	buffer_index = 0;
	buffer = zMalloc(buffer_size, "zReadFastaFile buffer");

	while ((c = (char) fgetc(stream)) != EOF) {
		if (c == '>') {
			(void)ungetc(c, stream);
			break;
		}
		if (isspace((int)c)) continue;

		buffer[buffer_index] = c;
		buffer_index++;

		if (buffer_index == buffer_size) {
			buffer_size += buffer_size;
			buffer = zRealloc(buffer, buffer_size, "zReadFastaFile buffer");
		}
	}

	entry->length = buffer_index;
	entry->seq = buffer;


	if (ferror(stream)) {
		zWarn("zReadFastaFile ferror");
		return 0;
	}
	if (entry->length == 0) {
		zWarn("zReadFastaFile no sequence");
		return 0;
	}

    return 1;
}
