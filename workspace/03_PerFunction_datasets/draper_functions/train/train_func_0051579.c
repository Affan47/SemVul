get_zipper(char *p) {
	int i;
	for (i = 0; i < sizeof(zippers)/sizeof(struct zipper); i++) {
		if (memcmp(p, zippers[i].pattern, zippers[i].length) == 0)
			return &zippers[i];
	}
	return NULL;
}
