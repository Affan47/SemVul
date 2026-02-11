check_pmoved(void)
{
#ifdef	USING_MMAP
	if  (Job_seg.dptr->js_psegid != Ptr_seg.inf.segsize)
#else
	if  (Job_seg.dptr->js_psegid != Ptr_seg.inf.base)
#endif
	{
#ifdef	USING_MMAP
		munmap(Ptr_seg.inf.seg, Ptr_seg.inf.segsize);
		Ptr_seg.inf.segsize = Ptr_seg.inf.reqsize = Job_seg.dptr->js_psegid;
		if  ((Ptr_seg.inf.seg = mmap(0, Ptr_seg.inf.segsize, PROT_READ|PROT_WRITE, MAP_SHARED, Ptr_seg.inf.mmfd, 0)) == MAP_FAILED)
#else
		shmdt(Ptr_seg.inf.seg);
		Ptr_seg.inf.base = Job_seg.dptr->js_psegid;
		if  ((Ptr_seg.inf.chan = shmget((key_t) Ptr_seg.inf.base, 0, 0)) < 0  ||
		     (Ptr_seg.inf.seg = shmat(Ptr_seg.inf.chan, (char *) 0, 0)) == (char *) -1)
#endif
			report(1123);
		Ptr_seg.dptr = (struct pshm_hdr *) Ptr_seg.inf.seg;
		Ptr_seg.Nptrs = Ptr_seg.dptr->ps_maxptrs;
		Ptr_seg.inf.segsize = Ptr_seg.inf.reqsize = sizeof(struct pshm_hdr) + SHM_PHASHMOD * sizeof(LONG) + Ptr_seg.Nptrs * sizeof(Hashspptr);
		Ptr_seg.hashp_pid = (LONG *) (Ptr_seg.inf.seg + sizeof(struct pshm_hdr));
		Ptr_seg.plist = (Hashspptr *) ((char *) Ptr_seg.hashp_pid + SHM_PHASHMOD*sizeof(LONG));
	}
}
