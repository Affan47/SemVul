kio_recv(struct kmsg *recvkmsg, int4 minlen, int fd_client)
{
	struct iovec	iov[2];
	char		*sv_msg;

	if (recvkmsg->k_flags & KNMSG) {
		sv_msg = ((struct nmsg *) (recvkmsg->k_msg))->nh_msg;
		iov[0].iov_base = recvkmsg->k_msg;
		iov[0].iov_len = sizeof(struct nmsg);
		iov[1].iov_base = ((struct nmsg *) (recvkmsg->k_msg))->nh_msg;
		iov[1].iov_len = minlen;

		if (mreadv(fd_client, iov, 2) < (int)(iov[0].iov_len +
				iov[1].iov_len)) return(LAMERROR);
		((struct nmsg *) (recvkmsg->k_msg))->nh_msg = sv_msg;
	} else {
		if (mread(fd_client, recvkmsg->k_msg, minlen) < minlen)
				return(LAMERROR);
	}

	return(0);
}
