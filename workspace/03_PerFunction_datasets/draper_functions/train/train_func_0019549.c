icmS15Fixed16Array_read(
	icmBase *pp,
	unsigned int len,
	unsigned int of
) {
	icmS15Fixed16Array *p = (icmS15Fixed16Array *)pp;
	icc *icp = p->icp;
	int rv = 0;
	unsigned int i, size;
	char *bp, *buf;

	if (len < 8) {
		sprintf(icp->err,"icmS15Fixed16Array_read: Tag too small to be legal");
		return icp->errc = 1;
	}


	if ((buf = (char *) icp->al->malloc(icp->al, len)) == NULL) {
		sprintf(icp->err,"icmS15Fixed16Array_read: malloc() failed");
		return icp->errc = 2;
	}
	bp = buf;


	if (   icp->fp->seek(icp->fp, of) != 0
	    || icp->fp->read(icp->fp, bp, 1, len) != len) {
		sprintf(icp->err,"icmS15Fixed16Array_read: fseek() or fread() failed");
		icp->al->free(icp->al, buf);
		return icp->errc = 1;
	}
	p->size = size = (len - 8)/4;

	if ((rv = p->allocate((icmBase *)p)) != 0) {
		icp->al->free(icp->al, buf);
		return rv;
	}


	if (((icTagTypeSignature)read_SInt32Number(bp)) != p->ttype) {
		sprintf(icp->err,"icmS15Fixed16Array_read: Wrong tag type for icmS15Fixed16Array");
		icp->al->free(icp->al, buf);
		return icp->errc = 1;
	}
	bp += 8;


	for (i = 0; i < size; i++, bp += 4) {
		p->data[i] = read_S15Fixed16Number(bp);
	}
	icp->al->free(icp->al, buf);
	return 0;
}
