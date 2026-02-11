GammaBuilder_lookupVariableType(CTX ctx, kTerm *tkN, kflag_t op)
{
	ktype_t itype = TYPE_var;
	kclass_t this_cid = DP(ctx->gma)->this_cid;
	ksymbol_t fn = Term_fn(ctx, tkN);
	if(FLAG_is(op, _VFINDTHIS)) {
		itype = Class_lookupVariableType(ctx, this_cid, fn);
	}
	if(itype == TYPE_var && FLAG_is(op, _VFINDSCRIPT) &&  this_cid != O_cid(K_GMASCR)) {
		itype = Class_lookupVariableType(ctx, O_cid(K_GMASCR), fn);
	}
	return itype;
}
