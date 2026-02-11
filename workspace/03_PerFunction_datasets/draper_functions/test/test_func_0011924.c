qrencodeStructured(const char *intext, const char *outfile)
{
	QRcode_List *qrlist, *p;
	char filename[FILENAME_MAX];
	char *base, *q, *suffix = NULL;
	int i = 1;

	base = strdup(outfile);
	if(base == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	if(strlen(base) > 4) {
		q = base + strlen(base) - 4;
		if(strcasecmp(".png", q) == 0) {
			suffix = strdup(q);
			*q = '\0';
		}
	}

	qrlist = encodeStructured(intext);
	if(qrlist == NULL) {
		perror("Failed to encode the input data:");
		exit(EXIT_FAILURE);
	}

	for(p = qrlist; p != NULL; p = p->next) {
		if(p->code == NULL) {
			fprintf(stderr, "Failed to encode the input data.\n");
			exit(EXIT_FAILURE);
		}
		if(suffix) {
			snprintf(filename, FILENAME_MAX, "%s-%02d%s", base, i, suffix);
		} else {
			snprintf(filename, FILENAME_MAX, "%s-%02d", base, i);
		}
		writePNG(p->code, filename);
		i++;
	}

	free(base);
	if(suffix) {
		free(suffix);
	}

	QRcode_List_free(qrlist);
}
