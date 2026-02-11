cvs_number_compare (cvs_number *a, cvs_number *b)

{
    int n = min (a->c, b->c);
    int i;

    for (i = 0; i < n; i++) {
	if (a->n[i] < b->n[i])
	    return -1;
	if (a->n[i] > b->n[i])
	    return 1;
    }
    if (a->c < b->c)
	return -1;
    if (a->c > b->c)
	return 1;
    return 0;
}
