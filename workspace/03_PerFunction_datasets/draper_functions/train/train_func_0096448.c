xpmGetString(mdata, sptr, l)
    xpmData *mdata;
    char **sptr;
    unsigned int *l;
{
    unsigned int i, n = 0;
    int c;
    char *p, *q, buf[BUFSIZ];

    if (!mdata->type) {
	if (mdata->cptr) {
	    char *start;
	    while (isspace(c = *mdata->cptr) && c != mdata->Eos)
		mdata->cptr++;
	    start = mdata->cptr;
	    while (c = *mdata->cptr)
		mdata->cptr++;
	    n = mdata->cptr - start + 1;
	    p = (char *) malloc(n);
	    if (!p)
		return (XpmNoMemory);
	    strncpy(p, start, n);
	}
    } else {
	FILE *file = mdata->stream.file;
	while (isspace(c = getc(file)) && c != mdata->Eos);
	if (c == EOF)
	    return (XpmFileInvalid);
	p = NULL;
	i = 0;
	q = buf;
	p = (char *) malloc(1);
	while (c != mdata->Eos && c != EOF) {
	    if (i == BUFSIZ) {


		q = (char *) realloc(p, n + i);
		if (!q) {
		    free(p);
		    return (XpmNoMemory);
		}
		p = q;
		q += n;

		strncpy(q, buf, i);
		n += i;
		i = 0;
		q = buf;
	    }
	    *q++ = c;
	    i++;
	    c = getc(file);
	}
	if (c == EOF) {
	    free(p);
	    return (XpmFileInvalid);
	}
	if (n + i != 0) {

	    q = (char *) realloc(p, n + i + 1);
	    if (!q) {
		free(p);
		return (XpmNoMemory);
	    }
	    p = q;
	    q += n;

	    strncpy(q, buf, i);
	    n += i;
	    p[n++] = '\0';
	} else {
	    *p = '\0';
	    n = 1;
	}
	ungetc(c, file);
    }
    *sptr = p;
    *l = n;
    return (XpmSuccess);
}
