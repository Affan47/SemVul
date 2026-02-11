collect_data(hashp, bufp, len, set)
	HTAB *hashp;
	BUFHEAD *bufp;
	int len, set;
{
	register u_int16_t *bp;
	register char *p;
	BUFHEAD *xbp;
	u_int16_t save_addr;
	int mylen, totlen;

	p = bufp->page;
	bp = (u_int16_t *)p;
	mylen = hashp->BSIZE - bp[1];
	save_addr = bufp->addr;

	if (bp[2] == FULL_KEY_DATA) {
		totlen = len + mylen;
		if (hashp->tmp_buf)
			free(hashp->tmp_buf);
		if ((hashp->tmp_buf = (char *)malloc(totlen)) == NULL)
			return (-1);
		if (set) {
			hashp->cndx = 1;
			if (bp[0] == 2) {
				hashp->cpage = NULL;
				hashp->cbucket++;
			} else {
				hashp->cpage =
				    __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
				if (!hashp->cpage)
					return (-1);
				else if (!((u_int16_t *)hashp->cpage->page)[0]) {
					hashp->cbucket++;
					hashp->cpage = NULL;
				}
			}
		}
	} else {
		xbp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
		if (!xbp || ((totlen =
		    collect_data(hashp, xbp, len + mylen, set)) < 1))
			return (-1);
	}
	if (bufp->addr != save_addr) {
		errno = EINVAL;
		return (-1);
	}
	memmove(&hashp->tmp_buf[len], (bufp->page) + bp[1], mylen);
	return (totlen);
}
