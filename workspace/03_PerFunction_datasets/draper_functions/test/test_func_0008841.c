Xfpurge(fp)
XFILE *fp;
{
	if (checkfp(fp, XS_RDONLY) < 0) return(EOF);

	fp -> status &= ~(XS_EOF | XS_READ);
	fp -> ptr = fp -> count = (ALLOC_T)0;

	return(0);
}
