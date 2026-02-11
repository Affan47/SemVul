xdr_array(xdrs, addrp, sizep, maxsize, elsize, elproc)
register XDR *xdrs;
char* *addrp;
unsigned int *sizep;
unsigned int maxsize;
unsigned int elsize;
xdrproc_t elproc;
{
	register unsigned int i;
	register char* target = *addrp;
	register unsigned int c;
	register bool_t stat = TRUE;
	register unsigned int nodesize;


	if (!xdr_u_int(xdrs, sizep)) {
		return (FALSE);
	}
	c = *sizep;
	if ((c > maxsize) && (xdrs->x_op != XDR_FREE)) {
		return (FALSE);
	}

	{
	  unsigned int i;
	  nodesize = 0;
	  for (i=c; i; --i) {
	    unsigned int tmp=nodesize+elsize;
	    if (tmp<nodesize)
	      return FALSE;
	    nodesize=tmp;
	  }
	}


	if (target == NULL)
		switch (xdrs->x_op) {
		case XDR_DECODE:
			if (c == 0)
				return (TRUE);
			*addrp = target = mem_alloc(nodesize);
			if (target == NULL) {
				(void) fprintf(stderr, "xdr_array: out of memory\n");
				return (FALSE);
			}
			memset(target, 0, nodesize);
			break;

		case XDR_FREE:
			return (TRUE);
		}


	for (i = 0; (i < c) && stat; i++) {
		stat = (*elproc) (xdrs, target, LASTUNSIGNED);
		target += elsize;
	}


	if (xdrs->x_op == XDR_FREE) {
		mem_free(*addrp, nodesize);
		*addrp = NULL;
	}
	return (stat);
}
