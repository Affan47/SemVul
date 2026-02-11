show_reference(const char *refname, const unsigned char *sha1,
			  int flag, void *cb_data)
{
	struct tag_filter *filter = cb_data;

	if (!fnmatch(filter->pattern, refname, 0)) {
		int i;
		unsigned long size;
		enum object_type type;
		char *buf, *sp, *eol;
		size_t len;

		if (!filter->lines) {
			printf("%s\n", refname);
			return 0;
		}
		printf("%-15s ", refname);

		buf = read_sha1_file(sha1, &type, &size);
		if (!buf || !size)
			return 0;


		sp = strstr(buf, "\n\n");
		if (!sp) {
			free(buf);
			return 0;
		}

		for (i = 0, sp += 2;
				i < filter->lines && sp < buf + size &&
				prefixcmp(sp, PGP_SIGNATURE "\n");
				i++) {
			if (i)
				printf("\n    ");
			eol = memchr(sp, '\n', size - (sp - buf));
			len = eol ? eol - sp : size - (sp - buf);
			fwrite(sp, len, 1, stdout);
			if (!eol)
				break;
			sp = eol + 1;
		}
		putchar('\n');
		free(buf);
	}

	return 0;
}
