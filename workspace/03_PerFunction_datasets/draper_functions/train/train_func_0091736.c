StmtExpr_p(CTX ctx, kOutputStream *w, kRawPtr *o, int level)
{
	kStmtExpr *stmt = (kStmtExpr*)o;
	kintptr_t i, size;
	L_TAILCALLED:;
	knh_putc(ctx, w, '(');
	if(!IS_FMTs(level)) {
		if(IS_Map(DP(stmt)->metaDictCaseMap)) {
			size = knh_Map_size(DP(stmt)->metaDictCaseMap);
			for(i = 0; i < size; i++) {
				kString *k = knh_DictMap_keyAt(DP(stmt)->metaDictCaseMap, i);
				kString *v = (kString*)knh_DictMap_valueAt(DP(stmt)->metaDictCaseMap, i);
				if(k == v) {
					knh_printf(ctx, w, "@%s ", S_totext(k));
				}
				else {
					knh_printf(ctx, w, "@%s(%O) ", S_totext(k), v);
				}
			}
		}
	}
	knh_write_ascii(ctx, w, TT__(stmt->stt));
	for(i = 0; i < DP(stmt)->size; i++) {
		knh_putc(ctx, w, ' ');
		knh_write_InObject(ctx, w, (Object*)(stmt->terms[i]), FMT_line);
	}
	knh_putc(ctx, w, ')');
	if(IS_FMTdump(level)) {
		if(SP(stmt)->type != TYPE_var) {
			knh_write(ctx, w, STEXT("+:")); knh_write_type(ctx, w, SP(stmt)->type);
		}
	}
	if(DP(stmt)->nextNULL != NULL) {
		if(IS_FMTdump(level)) {
			knh_write_EOL(ctx, w);
			stmt = DP(stmt)->nextNULL;
			goto L_TAILCALLED;
		}
		else {
			knh_write_dots(ctx, w);
		}
	}
}
