fqfstat(fq)

struct freq		*fq;

{
	int4		ret;
	struct fdesc	*f;

	f = fdfind(fq->fq_tfd);

	if (f == FDNULL) {
		fsendr(fq->fq_src_node, fq->fq_src_event,
				EBADF, (int4) LAMERROR, INT4_NIL, INT4_NIL);
	} else {
		fdactivate(f);
		ret = fmyfstat(f->f_fd, fbuf);
		fsendr(fq->fq_src_node, fq->fq_src_event, (ret == LAMERROR) ?
				errno : 0, ret, sizeof(struct stat), DINT4MSG);
	}
}
