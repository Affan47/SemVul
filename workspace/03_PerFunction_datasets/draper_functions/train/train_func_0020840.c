abbrev_dump(void)
{
	struct abbrmap *ab;
	int i, limit = sizeof(ab2name) / sizeof(struct abbrmap);

	fprintf(stderr, "ab2name: %d entries\n", limit);
	for (i = 0; i < limit; i++) {
		if (ab2name[i].c != 0) {
			fprintf(stderr, "ab2name[%d].c    = %c\n", i, ab2name[i].c);
			fprintf(stderr, "ab2name[%d].name = %s\n", i, ab2name[i].name);
		}
	}
	ab = (struct abbrmap *)varray_assign(name2ab, 0, 0);
	limit = name2ab->length;
	fprintf(stderr, "name2ab: %d entries\n", limit);
	for (i = 0; i < limit; i++) {
		if (ab[i].c != 0) {
			fprintf(stderr, "name2ab[%d].c    = %c\n", i, ab[i].c);
			fprintf(stderr, "name2ab[%d].name = %s\n", i, ab[i].name);
		}
	}
}
