multialloc(size_t s,
		 int d,
		 ...)
{
    va_list ap;
    int max,
     *q;
    char **r,

    **s1, *t, *tree;
    int i, j;
    int *d1;

    va_start(ap, d);
    d1 = (int *)G_malloc(d * sizeof(int));

    for (i = 0; i < d; i++)
	d1[i] = va_arg(ap, int);

    r = &tree;
    q = d1;
    max = 1;
    for (i = 0; i < d - 1; i++, q++) {

	max *= (*q);
	r[0] = (char *)G_malloc(max * sizeof(char **));
	r = (char **)r[0];

    }
    max *= s * (*q);
    r[0] = (char *)G_malloc(max * sizeof(char));


    r = (char **)tree;
    q = d1;
    max = 1;
    for (i = 0; i < d - 2; i++, q++) {

	max *= (*q);
	for (j = 1, s1 = r + 1, t = r[0]; j < max; j++) {


	    *s1 = (t += sizeof(char **) * *(q + 1));
	    s1++;
	}
	r = (char **)r[0];

    }
    max *= (*q);


    for (j = 1, s1 = r + 1, t = r[0]; j < max; j++)
	*s1++ = (t += s * *(q + 1));

    va_end(ap);
    G_free((char *)d1);

    return tree;
}
