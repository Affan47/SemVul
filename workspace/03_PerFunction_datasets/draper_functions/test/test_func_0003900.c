SWITCH_typing(CTX ctx, kStmtExpr *stmt, int needsRETURN)
{
	int hasReturn = 1, hasReturnCASE = 0;
	TYPING_UntypedExpr(ctx, stmt, 0);
	if(TT_(tkNN(stmt, 0)) == TT_LVAR) {
		KNH_SETv(ctx, tkNN(stmt, 2), tkNN(stmt, 0));
	}
	{
		BEGIN_BLOCK(stmt, esp);
		ktype_t type = Tn_type(stmt, 0);
		kTerm *tkIT = Tn_it(ctx, stmt, 2, type);
		int c = 0;
		kStmtExpr *stmtCASE, *stmtDEFAULT = NULL;
		stmtCASE = stmtNN(stmt, 1);
		while(stmtCASE != NULL) {
			if(STT_(stmtCASE) == STT_CASE) {
				Stmt_setESPIDX(ctx, stmtCASE);
				if(Tn_isASIS(stmtCASE, 0)) {
					if(stmtDEFAULT != NULL) {
						WarningDuplicatedDefault(ctx);
						knh_Stmt_done(ctx, stmtCASE);
						goto L_NEXT;
					}
					stmtDEFAULT = stmtCASE;
					goto L_STMT;
				}
				else if(!Tn_typing(ctx, stmtCASE, 0, type, _NOCHECK)) {
					knh_Stmt_done(ctx, stmtCASE);
					goto L_NEXT;
				}
				if(Tn_isCONST(stmtCASE, 0)) {
					kStmtExpr *stmtOP = new_StmtCASE(ctx, tkIT, tkNN(stmtCASE, 0));
					KNH_SETv(ctx, tmNN(stmtCASE, 0), stmtOP);
					if(!Tn_typing(ctx, stmtCASE, 0, TYPE_Boolean, _NOCAST)) {
						knh_Stmt_done(ctx, stmtCASE);
						goto L_NEXT;
					}
				}
				else {
					WarningNotConstant(ctx);
					knh_Stmt_done(ctx, stmtCASE);
					goto L_NEXT;
				}


				L_STMT:;
				hasReturnCASE = StmtITR_typing(ctx, stmtNN(stmtCASE, 1), needsRETURN);
				hasReturn = (hasReturn && hasReturnCASE);
				c++;
			}
			L_NEXT:;
			stmtCASE = DP(stmtCASE)->nextNULL;
		}
		if(c == 0) {
			return knh_Stmt_done(ctx, stmt);
		}
		Stmt_setSTOPITR(stmt, hasReturn);
		END_BLOCK(stmt, esp);
	}
	return TM(stmt);
}
