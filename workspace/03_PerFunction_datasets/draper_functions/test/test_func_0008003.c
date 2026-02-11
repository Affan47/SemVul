new_ReturnCppObject(CTX ctx, ksfp_t *sfp, void *rawptr, knh_Frawfree pfree)
{
	kMethod *mtd = sfp[K_MTDIDX].mtdNC;
	ktype_t rtype = knh_Param_rtype(DP(mtd)->mp);
	kRawPtr *npo = (kRawPtr*)new_hObject_(ctx, ClassTBL(rtype));
	npo->rawptr = rawptr;
	if(rawptr == NULL) {
		kObjectoNULL(ctx, npo);
	}
	else {
		npo->rawfree = (pfree != NULL) ? pfree : nofree;
	}
	return npo;
}
