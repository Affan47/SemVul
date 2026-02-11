ignore_format(int level) {
	static char buf[200];
	int i, comma = 0;

	buf[0] = 0;

	if (level == IGNORE_ALL)
		return "*";

	for (i = 0; ignore_labels[i].name; i++) {
		if (level & ignore_labels[i].level) {
			if (comma++)
				strlcat(buf, ",", sizeof(buf));

			strlcat(buf, ignore_labels[i].name, sizeof(buf));
		}
	}

	return buf;
}
