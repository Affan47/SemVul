print_word(FILE * fd, char **word, int *len, const int lead)
{
    int wlen, start, totlen;
    int nl;
    char *w, *b;

    start = *len;
    w = *word;

    nl = 0;
    while (*w == ' ' || *w == '\t' || *w == '\n')
	if (*w++ == '\n')
	    nl++;

    wlen = 0;
    for (b = w; *b != 0 && *b != ' ' && *b != '\t' && *b != '\n'; b++)
	wlen++;

    if (wlen == 0) {
	fprintf(fd, "\n");
	return 0;
    }

    if (start > lead) {
	totlen = start + wlen + 1;
    }
    else {
	totlen = start + wlen;
    }

    if (nl != 0 || totlen > 75) {
	while (--nl > 0)
	    fprintf(fd, "\n");
	fprintf(fd, "\n%*s", lead, "");
	start = lead;
    }

    if (start > lead) {
	fprintf(fd, " ");
	start++;
    }

    *len = start + wlen;

    fwrite(w, 1, wlen, fd);
    w += wlen;

    *word = w;

    return 1;
}
