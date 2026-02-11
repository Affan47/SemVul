write_newblock()
{
    if (wfd == -1)
	return ERR;
    if (write(wfd, (char *)wblkbuf, BLKSIZ) < BLKSIZ)
	return ERR;
    memset(wblkbuf, '\0', BLKSIZ);
    wp = wblkbuf;
    wblkno++;
    return OK;
}
