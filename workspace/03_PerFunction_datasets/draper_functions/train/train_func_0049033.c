CALL1_asm(CTX ctx, kStmtExpr *stmt, int espidx)
{
	Tn_asm(ctx, stmt, 0, espidx);
	if(IS_StmtExpr(DP(stmt)->stmtPOST)) {
		DP(DP(stmt)->stmtPOST)->espidx = espidx + 1;
		EXPR_asm(ctx, DP(stmt)->stmtPOST, espidx + 1);
	}
}
