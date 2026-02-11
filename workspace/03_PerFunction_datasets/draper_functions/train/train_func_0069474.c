reply_ptrupd(const int sock, const struct spdet *priv, const classcode_t classcode, const slotno_t slotno, const ULONG seq, const ULONG flags)
{
	const	struct	spptr	*pp;
	struct	spptr	inptr, rptr;

	pullin(sock, (char *) &inptr, sizeof(inptr));
	swapinp(&rptr, &inptr);
	if  (!(priv->spu_flgs & PV_PRINQ))  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrupd", "noperm");
		return  XT_NOPERM;
	}

	rerpfile();
	if  (!(flags & XT_FLAG_IGNORESEQ)  &&  seq != Ptr_seg.dptr->ps_serial)  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrupd", "seq");
		return  XT_SEQUENCE;
	}
	if  (slotno >= Ptr_seg.dptr->ps_maxptrs)  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrupd", "invslot");
		return  XT_INVALIDSLOT;
	}
	pp = &Ptr_seg.plist[slotno].p;
	if  (!check_valid_ptr(classcode, flags, pp, "ptrupd"))
		return  XT_UNKNOWN_PTR;
	if  (pp->spp_state >= SPP_PROC)  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrupd", "running");
		return  XT_PTR_RUNNING;
	}

	if  (rptr.spp_dev[0] == '\0' ||  rptr.spp_ptr[0] == '\0'  ||  rptr.spp_form[0] == '\0')  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrupd", "nullfld");
		return  XT_PTR_NULL;
	}


	if  (!(priv->spu_flgs & PV_ADDDEL)  &&  strcmp(rptr.spp_dev, pp->spp_dev) != 0)  {
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrupd", "nopriv");
		return  XT_PTR_CDEV;
	}


	sp_req.spr_un.p.spr_act = SP_CHGP;
	sp_req.spr_un.p.spr_pslot = slotno;
	sp_req.spr_un.p.spr_pid = getpid();
	while  (wpmsg(&sp_req, &rptr) != 0  &&  errno == EAGAIN)
		sleep(SLEEPTIME);
	if  (tracing & TRACE_APIOPEND)
		trace_op_res(Realuid, "ptrupd", "OK");
	return  XT_OK;
}
