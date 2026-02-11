rfc822_threadmsg(struct imap_refmsgtable *mt,
				     const char *msgidhdr,
				     const char *refhdr,
				     const char *subjheader,
				     const char *dateheader,
				     time_t dateheader_tm,
				     unsigned long seqnum)
{
	struct rfc822t *t;
	struct rfc822a *a;
	struct imap_refmsg *m;

	t=rfc822t_alloc_new(refhdr ? refhdr:"", NULL, NULL);
	if (!t)
	{
		return (0);
	}

	a=rfc822a_alloc(t);
	if (!a)
	{
		rfc822t_free(t);
		return (0);
	}

	m=rfc822_threadmsgaref(mt, msgidhdr, a, subjheader, dateheader,
			       dateheader_tm, seqnum);

	rfc822a_free(a);
	rfc822t_free(t);
	return m;
}
