getfoldedline(FILE * f, char *(*reader)(FILE *))
{


    static const char white[] = " \t";
    char *l1, *l2;
    int c;
    size_t len, oldlen;

    l1 = reader(f);
    if (!l1)
	return NULL;
    l2 = (char *)critmalloc((len = strlen(l1)) + 1, "getfoldedline");
    strcpy(l2, l1);


    if (*l2 && strcmp(l2, ".")) {
	for (;;) {
	    c = fgetc(f);
	    if (c != EOF) {
		ungetc(c, f);
		if (strchr(white, c)) {

		    l1 = reader(f);
		    if (l1) {
			oldlen = len;
			len += strlen(l1) + 1;
			l2 = (char *)critrealloc(l2, len + 2,
						   "getfoldedline");
			l2[oldlen++] = '\n';
			strcpy(l2 + oldlen, l1);
		    }
		} else {
		    break;
		}
	    } else {
		break;
	    }
	}
    }
    return l2;
}
