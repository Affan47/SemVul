GammaBuilder_tokenIDX(CTX ctx, kTerm *tk)
{
	if(TT_(tk) == TT_LVAR || TT_(tk) == TT_LFIELD) {
		knh_Array_add(ctx, DP(ctx->gma)->insts, tk);
	}
	return tk;
}
