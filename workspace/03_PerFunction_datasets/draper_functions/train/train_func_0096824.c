knh_InputStream_parseStmt(CTX ctx, kInputStream *in, kline_t *ul)
{
	BEGIN_LOCAL(ctx, lsfp, 2);
	DBG_ASSERT(ul[0] != 0);
	ctx->gma->uline = ul[0];
	kStmtExpr *rVALUE = new_Stmt2(ctx, STT_BLOCK, NULL);
	kTerm *tk = new_Term(ctx, TT_BRACE);
	KNH_SETv(ctx, lsfp[0].o, rVALUE);
	KNH_SETv(ctx, lsfp[1].o, tk);
	InputStream_parseTerm(ctx, in, ul, tk);
	DBG_(if(knh_isVerboseLang() ) {
		knh_write_Object(ctx, KNH_STDOUT, UPCAST(tk), FMT_dump);
	})
	if(TT_(tk) != TT_ERR) {
		tkitr_t tbuf, *titr = ITR_new(tk, &tbuf);
		_STMTs(ctx, rVALUE, titr);
		DBG_ASSERT(DP(rVALUE)->size == 1);
		if(IS_StmtExpr(stmtNN(rVALUE, 0))) {
			rVALUE = stmtNN(rVALUE, 0);
			DBG_(if(knh_isVerboseLang() ) {
				knh_write_Object(ctx, KNH_STDOUT, UPCAST(rVALUE), FMT_dump);
			})
			goto L_RETURN;
		}
	}
	kStmtExproERR(ctx, rVALUE, tk);
	L_RETURN:;
	END_LOCAL(ctx, lsfp);
	return rVALUE;
}
