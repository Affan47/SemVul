id_read_format(struct id *id, const char *buffer)
{
	int out = 0;


	while (*buffer) {

		if (*buffer == '-') {
			buffer++;
			continue;
		}

		if (out >= ID_LEN) {
			log_error("Too many characters to be uuid.");
			return 0;
		}

		id->uuid[out++] = *buffer++;
	}

	if (out != ID_LEN) {
		log_error("Couldn't read uuid: incorrect number of "
			  "characters.");
		return 0;
	}

	return id_valid(id);
}
