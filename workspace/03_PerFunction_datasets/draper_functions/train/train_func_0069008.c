groupCallback(unsigned short group, char *description, void *ctx)
{
    DCM_ELEMENT_NODE *n;
    LST_HEAD **l;

    l = (LST_HEAD **) ctx;
    n = calloc(1, sizeof(*n));
    if (n == NULL)
	return;

    n->e.tag = DCM_MAKETAG(group, 0);
    strcpy(n->e.description, description);

    (void) LST_Enqueue(l, n);
}
