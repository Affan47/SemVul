reply_ptrread(const int sock, const classcode_t classcode, const slotno_t slotno, const ULONG seq, const ULONG flags)
{
	const  struct  spptr  *pp;

	rerpfile();
	if  (!(flags & XT_FLAG_IGNORESEQ)  &&  seq != Ptr_seg.dptr->ps_serial)  {
		err_result(sock, XT_SEQUENCE, Ptr_seg.dptr->ps_serial);
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrread", "seq");
		return;
	}
	if  (slotno >= Ptr_seg.dptr->ps_maxptrs)  {
		err_result(sock, XT_INVALIDSLOT, Ptr_seg.dptr->ps_serial);
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrread", "invslot");
		return;
	}

	pp = &Ptr_seg.plist[slotno].p;
	if  (check_valid_ptr(classcode, flags, pp, "ptrread"))  {
		struct	api_msg	outmsg;
		outmsg.code = API_PTRREAD;
		outmsg.retcode = 0;
		outmsg.un.r_reader.seq = htonl(Ptr_seg.dptr->ps_serial);
		pushout(sock, (char *) &outmsg, sizeof(outmsg));
		ptr_read_rest(sock, pp);
		if  (tracing & TRACE_APIOPEND)
			trace_op_res(Realuid, "ptrread", "OK");
	}
	else
		err_result(sock, XT_UNKNOWN_PTR, Ptr_seg.dptr->ps_serial);
}
