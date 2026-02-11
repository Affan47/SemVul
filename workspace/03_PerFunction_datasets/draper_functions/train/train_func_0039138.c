dotrunc(struct pend_job *pj, const LONG size)
{
#ifdef	HAVE_FTRUNCATE
	if  (ftruncate(fileno(pj->out_f), size) < 0)
		return  1;
	pj->jobout.spq_size = size;
#else
	char	*tnam = mkspid("TMP", pj->jobout.spq_job);
	int	ch, fd;
	LONG	cnt = 0;
	FILE	*tf;
	if  ((fd = open(tnam, O_RDWR|O_CREAT|O_TRUNC|O_EXCL, 0400)) < 0  ||  !(tf = fdopen(fd, "w+")))
		return  1;
	rewind(pj->out_f);
	while  ((ch = getc(pj->out_f)) != EOF  &&  cnt < size)  {
		putc(ch, tf);
		cnt++;
	}
	pj->jobout.spq_size = cnt;
	fclose(pj->out_f);
	pj->out_f = tf;
	rewind(tf);
	if  (unlink(pj->tmpfl) < 0  ||  link(tnam, pj->tmpfl) < 0  ||  unlink(tnam) < 0)
		return  1;
#endif
	return  0;
}
