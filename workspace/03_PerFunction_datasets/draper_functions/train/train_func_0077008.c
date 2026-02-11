Xferror(fp)
XFILE *fp;
{
	if (checkfp(fp, 0) < 0) return(-1);

	return(fp -> status & XS_ERROR);
}
