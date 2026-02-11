mastr_new(size_t size)
{
    mastr *n;

    assert(size != 0);

    n = (mastr *)malloc(sizeof(mastr));
    if (!n) {
	mastr_oom();
	 return NULL;
    }
    n->bufsize = size + 1;
    if (!(n->dat = (char *)malloc(n->bufsize))) {
	free(n);
	mastr_oom();
	 return NULL;
    }
    n->dat[0] = '\0';
    n->len = 0;
    return n;
}
