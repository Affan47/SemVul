_PARAMs(CTX ctx, kStmtExpr *stmt, tkitr_t *itr)
{
	kStmtExpr *stmtP = new_Stmt2(ctx, STT_DECL, NULL);
	int e = itr->e, ridx = ITR_indexTT(itr, TT_DARROW, -1);
	if(ridx != -1) itr->e = ridx;
	int varidx = ITR_indexTT(itr, TT_DOTS, -1);
	if(varidx != -1) {
		DBG_P("******** @Vargs **********");
		StmtMETHOD_setVARGs(stmt,  1);
		itr->e = varidx;
	}
	knh_Stmt_add(ctx, stmt, stmtP);

	while(ITR_hasNext(itr)) {
		int idx = ITR_indexTT(itr, TT_COMMA, itr->e);
		tkitr_t abuf, *aitr = ITR_first(itr, idx, &abuf, +1);
		while(ITR_is(aitr, TT_METAN)) {
			DBG_P("TODO: parameter annotation");
			ITR_next(aitr);
		}
		if(ITR_is(aitr, TT_VOID)) {
			break;
		}
		if(ITR_isT(aitr, isTYPE)) {
			knh_Stmt_add(ctx, stmtP, ITR_nextTK(aitr));
		}
		if(DP(stmtP)->size % 3 != 1) {
			_VAR(ctx, stmtP, aitr);
		}
		if(ITR_isT(aitr, isVARN)) {
			kTerm *tkN = ITR_nextTK(aitr);
			knh_Stmt_add(ctx, stmtP, tkN);
		}
		else {
			_ERROR(ctx, stmt, aitr, _("variable"));
		}
		if(ITR_is(aitr, TT_LET)) {
			ITR_next(aitr);
			_EXPR(ctx, stmtP, aitr);
		}
		else {
			_ASIS(ctx, stmtP, aitr);
		}
	}
	if(ridx != -1) itr->e = e;
}
