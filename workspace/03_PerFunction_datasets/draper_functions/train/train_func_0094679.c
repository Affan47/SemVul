check_jmoved(void)
{
#ifdef	USING_MMAP
	if  (Job_seg.dinf.segsize != Job_seg.dptr->js_did)  {
		munmap(Job_seg.dinf.seg, Job_seg.dinf.segsize);
		Job_seg.dinf.segsize = Job_seg.dinf.reqsize = Job_seg.dptr->js_did;
		Job_seg.Njobs = Job_seg.dptr->js_maxjobs;
		if  ((Job_seg.dinf.seg = mmap(0, Job_seg.dinf.segsize, PROT_READ|PROT_WRITE, MAP_SHARED, Job_seg.dinf.mmfd, 0)) == MAP_FAILED)
			report(1122);
		Job_seg.jlist = (Hashspq *) Job_seg.dinf.seg;
	}
#else
	if  (Job_seg.dinf.base != Job_seg.dptr->js_did)  {
		shmdt((char *) Job_seg.dinf.seg);
		Job_seg.dinf.base = Job_seg.dptr->js_did;
		Job_seg.Njobs = Job_seg.dptr->js_maxjobs;
		Job_seg.dinf.segsize = Job_seg.dinf.reqsize = Job_seg.Njobs * sizeof(Hashspq);
		if  ((Job_seg.dinf.chan = shmget((key_t) Job_seg.dinf.base, 0, 0)) <= 0  ||
		     (Job_seg.dinf.seg = shmat(Job_seg.dinf.chan, (char *) 0, 0)) == (char *) -1)
			report(1122);
		Job_seg.jlist = (Hashspq *) Job_seg.dinf.seg;
	}
#endif
}
