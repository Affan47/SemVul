FOREACH1_typing(CTX ctx, kStmtExpr *stmt)
{
	kStmtExpr *stmtDECL = stmtNN(stmt, 0);

	BEGIN_BLOCK(stmt, esp);
	kclass_t itrcid = CLASS_unknown;
	kTerm *tkT = TTYPE_typing(ctx, tkNN(stmtDECL, 0), TYPE_var);
	kTerm *tkN = tkNN(stmtDECL, 1);
	ksymbol_t fn = Term_fn(ctx, tkN);
	kclass_t p1 = tkT->cid;
	if(p1 == TYPE_var) {
		kTerm *tkN2 = TNAME_typing(ctx, tkN, TYPE_dyn, _FINDLOCAL | _FINDFIELD | _FINDSCRIPT | _USEDCOUNT);
		if(tkN2 == NULL) {
			TYPING(ctx, stmt, 1, TYPE_dyn, _NOCHECK);
			tkT = FOREACH1_toIterator(ctx, stmt, 1);
			if(TT_(tkT) == TT_ERR) return tkT;
			itrcid = Tn_cid(stmt, 1);
			p1 = C_p1(itrcid);
			KNH_SETv(ctx, tkNN(stmt, 0), GammaBuilder_addLVAR(ctx, 0, p1, fn, 1));
			INFO_Typing(ctx, "", TK_tobytes(tkN), p1);
			Tn_it(ctx, stmt, 2, itrcid);
			goto L_BLOCK;
		}
		p1 = tkN2->type;
		if(TT_(tkN2) != TT_LVAR || TT_(tkN2) != TT_FVAR) {
			KNH_SETv(ctx, tkNN(stmt, 0), GammaBuilder_addLVAR(ctx, 0, p1, fn, 1));
		}
		else {
			KNH_SETv(ctx, tkNN(stmt, 0), tkN);
		}
	}
	else {
		KNH_SETv(ctx, tkNN(stmt, 0), GammaBuilder_addLVAR(ctx, 0, p1, fn, 1));
	}
	itrcid = knh_class_P1(ctx, CLASS_Iterator, p1);
	TYPING(ctx, stmt, 1, itrcid, _COERCION);
	Tn_it(ctx, stmt, 2, itrcid);

	L_BLOCK:;
	TYPING_Block(ctx, stmt, 3);
	END_BLOCK(stmt, esp);
	return Stmt_typed(ctx, stmt, TYPE_void);
}
