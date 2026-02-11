StmtExpr_free(CTX ctx, kRawPtr *o)
{
	kStmtExpr *stmt = (kStmtExpr*)o;
	knh_StmtEX_t *b = DP((kStmtExpr*)o);
	if(stmt->terms != NULL) {
		KNH_FREE(ctx, stmt->terms, sizeof(kTerm*) * b->capacity);
		stmt->terms = NULL;
	}
	knh_bodyfree(ctx, b, Stmt);
}
