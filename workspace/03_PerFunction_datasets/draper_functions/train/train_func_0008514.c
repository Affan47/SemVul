buffalloc(len)
    unsigned len;
{
    if ((bufp = holdbuf = (char *) malloc(len)) == NULL)
	error("out of memory");
    bufend = holdbuf + len;
}
