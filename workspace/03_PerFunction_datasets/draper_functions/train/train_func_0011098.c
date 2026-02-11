kParamocid(CTX ctx, kParam *pa, kclass_t this_cid, kParam *npa)
{
	size_t i, size = pa->psize + pa->rsize;
	for(i = 0; i < size; i++) {
		kparam_t *cp = knh_Param_get(pa, i);
		kparam_t np = *cp;
		np.type = ktype_tocid(ctx, np.type, this_cid);
		knh_Param_add(ctx, npa, np);
	}
	npa->psize = pa->psize;
	npa->rsize = pa->rsize;
}
