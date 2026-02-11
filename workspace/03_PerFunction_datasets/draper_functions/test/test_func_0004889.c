Range_reftrace(CTX ctx, kRawPtr *o FTRARG)
{
	kRange *rng = (kRange*)o;
	if(!Range_isNDATA(o)) {
		KNH_ADDREF(ctx, rng->ostart);
		KNH_ADDREF(ctx, rng->oend);
		KNH_SIZEREF(ctx);
	}
}
