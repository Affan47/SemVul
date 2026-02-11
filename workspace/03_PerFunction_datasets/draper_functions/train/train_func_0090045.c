prune_origin(const char *name, const char *origin) {
	const char *oname = name;

	while (*name != '\0') {
		if (origin != NULL && ns_samename(name, origin) == 1)
			return (name - oname - (name > oname));
		while (*name != '\0') {
			if (*name == '\\') {
				name++;

				if (*name == '\0')
					break;
			} else if (*name == '.') {
				name++;
				break;
			}
			name++;
		}
	}
	return (name - oname);
}
