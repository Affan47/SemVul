DECLFIELD_typing(CTX ctx, kStmtExpr *stmt, size_t i)
{
	kflag_t flag  = DECL_flag(ctx, stmt, _FGETTER | _FSETTER);
	kTerm *tkT = DECL3_typing(ctx, stmt, i, TYPE_var, _VFINDSCRIPT, 0);
	if(TT_(tkT) != TT_ERR) {
		return GammaBuilder_add(ctx, flag, tkT, tkNN(stmt,i+1), tkNN(stmt,i+2), GF_UNIQUE|GF_FIELD|GF_USEDCOUNT);
	}
	return tkT;
}
