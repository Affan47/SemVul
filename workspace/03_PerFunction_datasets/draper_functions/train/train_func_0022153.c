get_esl_comment_lines (FILE *fp)
{
    char s[MAXLEN], *buf = NULL;
    int count = 0, bigger = 1;

    if (fgets(s, sizeof s, fp) == NULL) {
	return NULL;
    }

    if (!strncmp(s, STARTCOMMENT, 2)) {
	buf = malloc(20 * MAXLEN);

	if (buf == NULL) {
	    return NULL;
	}

	*buf = '\0';
	while (fgets(s, sizeof s, fp)) {
	    if (!strncmp(s, ENDCOMMENT, 2)) {
		break;
	    }
	    if (++count > 20 * bigger) {
		size_t bufsize = 20 * MAXLEN * ++bigger;
		char *tmp = realloc(buf, bufsize);

		if (tmp == NULL) {
		    free(buf);
		    return NULL;
		} else {
		    buf = tmp;
		}
	    }
	    strcat(buf, s);
	}
    }

    return buf;
}
