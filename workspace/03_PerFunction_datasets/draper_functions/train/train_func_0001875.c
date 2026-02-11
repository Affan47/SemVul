GammaBuilder_addLVAR(CTX ctx, kflag_t flag, ktype_t type, ksymbol_t fn, int ucnt)
{
	kindex_t idx = DP(ctx->gma)->gsize;
	knh_gamma2_t *gf = DP(ctx->gma)->gf;
	kTerm *tkIDX = new_TermTYPED(ctx, TT_LVAR, type, idx - DP(ctx->gma)->fvarsize);
	if(!(idx < DP(ctx->gma)->gcapacity)) {
		gf = GammaBuilder_expand(ctx, ctx->gma, 4);
	}
	gf[idx].flag  = flag;
	gf[idx].type  = type;
	gf[idx].fn    = fn;
	gf[idx].ucnt  = ucnt;
	KNH_SETv(ctx, gf[idx].tkIDX, GammaBuilder_tokenIDX(ctx, tkIDX));
	DP(ctx->gma)->gsize += 1;
	return gf[idx].tkIDX;
}
