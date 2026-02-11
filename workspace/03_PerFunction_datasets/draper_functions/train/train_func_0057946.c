knh_loadScriptParam(CTX ctx, const kloaddata_t **d, kuintptr_t uflag, int step)
{
	kParam *pa = new_Param(ctx);
	const kloaddata_t *data = (*d) + step;
	long i, psize = (long)data[0];
	long rsize = (long)data[1];
	data += 2;
	for(i = 0; i < psize+rsize; i++) {
		ktype_t type = (data[0] < _MAX || (TYPE_This <= data[0] && data[0] <= TYPE_T3)) ?
			(ktype_t)data[0] : knh_NameSpace_gettype(ctx, K_GMANS, kloaddata_tobytes(data[0]));
		ksymbol_t fn = (data[1] < _MAX) ?
			(ksymbol_t)data[1] : knh_getfnq(ctx, kloaddata_tobytes(data[1]), FN_NEWID);
		kparam_t p = {type, fn};
		knh_Param_add(ctx, pa, p);
		data += 2;
	}
	pa->psize = (kushort_t)psize;
	pa->rsize = (kushort_t)rsize;
	*d = data;
	pa->h.magicflag |= uflag;
	return pa;
}
