kio_transfer(struct kmsg *sendkmsg, int fd_send, int fd_recv, int4 minlen)
{
	int4		remain;
	int4		len;

	remain = minlen;

	if (sendkmsg->k_flags & KNMSG) {
		remain += sizeof(struct nmsg);
	}


	while (remain > 0) {
		len = (remain > KPKTLEN) ? KPKTLEN : remain;
		mread(fd_send, fwdbuf, len);
		mwrite(fd_recv, fwdbuf, len);
		remain -= len;
	}
}
