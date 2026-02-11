print_strs(const struct dcmi_cmd * vs, const char * title, int loglevel,
		int verthorz)
{
	int i;

	if (vs == NULL)
		return;

	if (title != NULL) {
		if (loglevel < 0)
			printf("\n%s\n", title);
		else
			lprintf(loglevel, "\n%s", title);
	}
	for (i = 0; vs[i].str != NULL; i++) {
		if (loglevel < 0) {
			if (vs[i].val < 256)
				if (verthorz == 0)
					printf("    %s    %s\n", vs[i].str, vs[i].desc);
				else
					printf("%s", vs[i].str);
			else if (verthorz == 0)
				printf("    %s    %s\n", vs[i].str, vs[i].desc);
			else
				printf("%s", vs[i].str);
		} else {
			if (vs[i].val < 256)
				lprintf(loglevel, "    %s    %s", vs[i].str, vs[i].desc);
			else
				lprintf(loglevel, "    %s    %s", vs[i].str, vs[i].desc);
		}


		if ((verthorz == 1) && (vs[i+1].str != NULL))
			printf(" | ");
	}
	if (verthorz == 0) {
		if (loglevel < 0) {
			printf("\n");
		} else {
			lprintf(loglevel, "");
		}
	}
}
