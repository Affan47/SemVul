io_load(struct io *io, const char *separators,
	int (*read_property)(char *, size_t, char *, size_t))
{
	char *name;
	int state = OK;

	if (!io_start(io))
		return ERR;

	while (state == OK && (name = io_get(io, '\n', TRUE))) {
		char *value;
		size_t namelen;
		size_t valuelen;

		name = chomp_string(name);
		namelen = strcspn(name, separators);

		if (name[namelen]) {
			name[namelen] = 0;
			value = chomp_string(name + namelen + 1);
			valuelen = strlen(value);

		} else {
			value = "";
			valuelen = 0;
		}

		state = read_property(name, namelen, value, valuelen);
	}

	if (state != ERR && io_error(io))
		state = ERR;
	io_done(io);

	return state;
}
