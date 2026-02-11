closeit(Dict_t ** d)
{
    int i;

    for (i = 0; i < 3; i++) {
	if (d[i]) {
	    dtclose(d[i]);
	    d[i] = NIL(Dict_t *);
	}
    }
}
