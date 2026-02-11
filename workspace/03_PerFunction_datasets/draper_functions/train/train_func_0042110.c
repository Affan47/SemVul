do_store(
        pTHX_
	PerlIO *f,
	SV *sv,
	int optype,
	int network_order,
	SV **res)
{
	dSTCXT;
	int status;

	ASSERT(!(f == 0 && !(optype & ST_CLONE)) || res,
		("must supply result SV pointer for real recursion to memory"));

	TRACEME(("do_store (optype=%d, netorder=%d)",
		optype, network_order));

	optype |= ST_STORE;


	if (cxt->s_dirty)
		clean_context(aTHX_ cxt);


	if (cxt->entry)
		cxt = allocate_context(aTHX_ cxt);

	cxt->entry++;

	ASSERT(cxt->entry == 1, ("starting new recursion"));
	ASSERT(!cxt->s_dirty, ("clean context"));


	if (!SvROK(sv))
		CROAK(("Not a reference"));
	sv = SvRV(sv);


	if (!f)
		MBUF_INIT(0);


	init_store_context(aTHX_ cxt, f, optype, network_order);

	if (-1 == magic_write(aTHX_ cxt))
		return 0;


	ASSERT(is_storing(aTHX), ("within store operation"));

	status = store(aTHX_ cxt, sv);


	if (!cxt->fio && res)
		*res = mbuf2sv(aTHX);


	clean_store_context(aTHX_ cxt);
	if (cxt->prev && !(cxt->optype & ST_CLONE))
		free_context(aTHX_ cxt);

	TRACEME(("do_store returns %d", status));

	return status == 0;
}
