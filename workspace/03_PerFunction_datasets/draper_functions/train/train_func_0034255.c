GammaBuilder_add(CTX ctx, kflag_t flag, kTerm *tkT, kTerm *tkN, kTerm *tkV, kflag_t op)
{
	kindex_t idx = 0;
	knh_gamma2_t *gf = DP(ctx->gma)->gf;
	ksymbol_t fn = Term_fn(ctx, tkN);
	ktype_t type = (tkT)->cid;

	if(FLAG_is(op, GF_UNIQUE)) {
		for(idx = 0; idx < DP(ctx->gma)->gsize; idx++) {
			if(gf[idx].fn == fn) {
				if(gf[idx].type == type) return gf[idx].tkIDX;
				return ERROR_AlreadyDefinedType(ctx, fn, type);
			}
		}
	}

	idx = DP(ctx->gma)->gsize;
	if(!(idx < DP(ctx->gma)->gcapacity)) {
		gf = GammaBuilder_expand(ctx, ctx->gma, 4);
	}
	if(FLAG_is(op, GF_FUNCVAR)) {
		kTermoTYPED(ctx, tkN, TT_FVAR, type, idx);
		STRICT_(Term_setReadOnly(tkN, 1));
		DP(ctx->gma)->fvarsize += 1;
	}
	else {
		kTermoTYPED(ctx, tkN, TT_LVAR, type, idx - DP(ctx->gma)->fvarsize);
		Term_setReadOnly(tkN, FLAG_is(flag, _FREADONLY));
	}
	gf[idx].flag  = flag;
	gf[idx].type  = type;
	gf[idx].fn    = fn;
	gf[idx].ucnt  = FLAG_is(op, GF_USEDCOUNT) ? 1 : 0;
	if(tkV != NULL && TT_(tkV) == TT_CONST) {
		KNH_SETv(ctx, gf[idx].tk, tkV);
	}
	KNH_SETv(ctx, gf[idx].tkIDX, GammaBuilder_tokenIDX(ctx, tkN));
	DP(ctx->gma)->gsize += 1;
	DBLNDATA_(if(FLAG_is(op, GF_FIELD) && IS_Tunbox(type)) {
		idx = DP(ctx->gma)->gsize;
		if(!(idx < DP(ctx->gma)->gcapacity)) {
			gf = GammaBuilder_expand(ctx, ctx->gma, 4);
		}
		gf[idx].flag  = 0;
		gf[idx].type  = TYPE_void;
		gf[idx].fn    = FN_;
		gf[idx].ucnt  = 1;
		DP(ctx->gma)->gsize += 1;
	})
	return tkN;
}
