bfa_nw_ioc_attach(struct bfa_ioc *ioc, void *bfa, struct bfa_ioc_cbfn *cbfn)
{
	ioc->bfa	= bfa;
	ioc->cbfn	= cbfn;
	ioc->fcmode	= false;
	ioc->pllinit	= false;
	ioc->dbg_fwsave_once = true;
	ioc->iocpf.ioc  = ioc;

	bfa_ioc_mbox_attach(ioc);
	INIT_LIST_HEAD(&ioc->notify_q);

	bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
	bfa_fsm_send_event(ioc, IOC_E_RESET);
}
