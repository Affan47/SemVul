_METHOD(CTX ctx, kStmtExpr *stmt, tkitr_t *itr)
{
	kTerm *tkT = ITR_nextTK(itr);
	knh_Stmt_add(ctx, stmt, tkT);
	if(TT_(tkT) == TT_FUNCTION) TT_(tkT) = TT_ASIS;
	if(ITR_is(itr, TT_UNAME)) {
		Stmt_tadd(ctx, stmt, itr, isCLASSAME, _("class name"));
	}
	else {
		_ASIS(ctx, stmt, itr);
	}
	Stmt_taddASIS(ctx, stmt, itr, isMN);
	ADD(stmt, _PARAM(ctx, stmt, itr));
	ADD(stmt, _CODE(ctx, stmt, itr));
}
