Ns_ConnSend(Ns_Conn *conn, struct iovec *bufs, int nbufs)
{
    Conn	   *connPtr = (Conn *) conn;
    int         nwrote, towrite, i, n;
    struct iovec    sbufs[16];


    towrite = 0;
    n = 0;
    if (connPtr->obuf.length > 0) {
	sbufs[n].iov_base = connPtr->obuf.string;
	sbufs[n].iov_len = connPtr->obuf.length;
	towrite += sbufs[n].iov_len;
	++n;
    }
    for (i = 0; i < nbufs && n < 16; ++i) {
	if (bufs[i].iov_len > 0 && bufs[i].iov_base != NULL) {
	    sbufs[n].iov_base = bufs[i].iov_base;
	    sbufs[n].iov_len = bufs[i].iov_len;
	    towrite += bufs[i].iov_len;
	    ++n;
	}
    }
    nbufs = n;
    bufs = sbufs;
    n = nwrote = 0;
    while (towrite > 0) {
	n = NsConnSend(conn, bufs, nbufs);
	if (n < 0) {
	    break;
	}
	towrite -= n;
	nwrote  += n;
	if (towrite > 0) {
	    for (i = 0; i < nbufs && n > 0; ++i) {
		if (n > (int) bufs[i].iov_len) {
		    n -= bufs[i].iov_len;
		    bufs[i].iov_base = NULL;
		    bufs[i].iov_len = 0;
		} else {
		    bufs[i].iov_base = (char *) bufs[i].iov_base + n;
		    bufs[i].iov_len -= n;
		    n = 0;
		}
	    }
	}
    }
    if (nwrote > 0) {
        connPtr->nContentSent += nwrote;
	if (connPtr->obuf.length > 0) {
	    n = connPtr->obuf.length - nwrote;
	    if (n <= 0) {
		nwrote -= connPtr->obuf.length;
		Tcl_DStringTrunc(&connPtr->obuf, 0);
	    } else {
		memmove(connPtr->obuf.string,
		    connPtr->obuf.string + nwrote, (size_t)n);
		Tcl_DStringTrunc(&connPtr->obuf, n);
		nwrote = 0;
	    }
	}
    } else {


        nwrote = n;
    }
    return nwrote;
}
