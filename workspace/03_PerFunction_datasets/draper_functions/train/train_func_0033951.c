icmSignature_write(
	icmBase *pp,
	unsigned int of
) {
	icmSignature *p = (icmSignature *)pp;
	icc *icp = p->icp;
	unsigned int len;
	char *bp, *buf;
	int rv = 0;


	if ((len = p->get_size((icmBase *)p)) == UINT_MAX) {
		sprintf(icp->err,"icmSignature_write get_size overflow");
		return icp->errc = 1;
	}
	if ((buf = (char *) icp->al->malloc(icp->al, len)) == NULL) {
		sprintf(icp->err,"icmSignature_write malloc() failed");
		return icp->errc = 2;
	}
	bp = buf;


	if ((rv = write_SInt32Number((int)p->ttype,bp)) != 0) {
		sprintf(icp->err,"icmSignature_write: write_SInt32Number() failed");
		icp->al->free(icp->al, buf);
		return icp->errc = rv;
	}
	write_SInt32Number(0,bp+4);


	if ((rv = write_SInt32Number((int)p->sig, bp + 8)) != 0) {
		sprintf(icp->err,"icmSignaturea_write: write_SInt32Number() failed");
		icp->al->free(icp->al, buf);
		return icp->errc = rv;
	}


	if (   icp->fp->seek(icp->fp, of) != 0
	    || icp->fp->write(icp->fp, buf, 1, len) != len) {
		sprintf(icp->err,"icmSignature_write fseek() or fwrite() failed");
		icp->al->free(icp->al, buf);
		return icp->errc = 2;
	}
	icp->al->free(icp->al, buf);
	return 0;
}
