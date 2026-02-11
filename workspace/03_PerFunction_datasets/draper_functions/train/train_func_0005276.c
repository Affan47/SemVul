lam_rfclose(int fd)
{
	struct nmsg	nhead;
	struct freq	*request;
	struct freply	*reply;
	int		mask;


	if (_fdvalid(fd))
          return(LAMERROR);

        LAM_ZERO_ME(nhead);
	request = (struct freq *) nhead.nh_data;
	reply = (struct freply *) nhead.nh_data;

	request->fq_src_node = getnodeid();
	request->fq_src_event = -lam_getpid();
	request->fq_req = FQCLOSE;
	request->fq_tfd = _ufd[fd].fu_tfd;

	if ((fd <= 2) && (_ufd[fd].fu_node == NOTNODEID)) {
		_ufd[fd].fu_node = getorigin();
	}

	nhead.nh_node = _ufd[fd].fu_node;
	nhead.nh_event = EVFILED;
	nhead.nh_type = 0;
	nhead.nh_flags = 0;
	nhead.nh_length = 0;
	nhead.nh_msg = 0;
	mask = ksigblock(sigmask(SIGUDIE) | sigmask(SIGARREST));

	if (nsend(&nhead)) {
		ksigsetmask(mask);
		return(LAMERROR);
	}

	nhead.nh_event = -lam_getpid();

	if (nrecv(&nhead)) {
		ksigsetmask(mask);
		return(LAMERROR);
	}

	ksigsetmask(mask);

	if (reply->fr_errno != 0) {
		errno = reply->fr_errno;
		return(LAMERROR);
	} else {
		_ufd[fd].fu_tflags = 0;
		return(0);
	}
}
