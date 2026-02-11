_dxf_SetExceedSocket(int fd, void *d)
{
	int i;
	EXRIH r;

	for (i = 0, r = handlers; i < nRIH; i++, r++)
    	if (r->fd == fd)
		{
			r->dpy = d;
			r->isWin = 1;
			return 1;
		}

	return 0;
}
