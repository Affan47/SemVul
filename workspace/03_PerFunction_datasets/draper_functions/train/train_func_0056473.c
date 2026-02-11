putpair(char *pag, datum key, datum val)
{
	register int n;
	register int off;
	register short *ino = (short *) pag;

	off = ((n = GET_SHORT(ino,0)) > 0) ? GET_SHORT(ino,n) : PBLKSIZ;


	off -= key.dsize;
	if (key.dsize)
		(void) memcpy(pag + off, key.dptr, key.dsize);
	PUT_SHORT(ino,n + 1,off);


	off -= val.dsize;
	if (val.dsize)
		(void) memcpy(pag + off, val.dptr, val.dsize);
	PUT_SHORT(ino,n + 2,off);


	PUT_SHORT(ino,0,GET_SHORT(ino,0) + 2);
}
