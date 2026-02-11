bfa_sfp_getdata(struct bfa_sfp_s *sfp, enum bfi_sfp_mem_e memtype)
{
	struct bfi_sfp_req_s *req = (struct bfi_sfp_req_s *)sfp->mbcmd.msg;

	WARN_ON(sfp->lock != 0);
	bfa_trc(sfp, sfp->state);

	sfp->lock = 1;
	sfp->memtype = memtype;
	req->memtype = memtype;


	bfa_alen_set(&req->alen, sizeof(struct sfp_mem_s), sfp->dbuf_pa);

	bfa_sfp_getdata_send(sfp);
}
