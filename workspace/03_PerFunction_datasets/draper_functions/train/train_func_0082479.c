dgl_mempop(unsigned char *pstack, long *istack, long size)
{
    if (*istack == 0)
	return NULL;
    return &pstack[size * (--(*istack))];
}
