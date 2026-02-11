pat_idx_list_reg(struct pattern_expr *expr, struct pattern *pat, char **err)
{
	struct pattern_list *patl;


	patl = calloc(1, sizeof(*patl));
	if (!patl) {
		memprintf(err, "out of memory while indexing pattern");
		return 0;
	}


	memcpy(&patl->pat, pat, sizeof(*pat));


	patl->pat.ptr.reg = calloc(1, sizeof(*patl->pat.ptr.reg));
	if (!patl->pat.ptr.reg) {
		free(patl);
		memprintf(err, "out of memory while indexing pattern");
		return 0;
	}


	if (!regex_comp(pat->ptr.str, patl->pat.ptr.reg, !(expr->mflags & PAT_MF_IGNORE_CASE), 0, err)) {
		free(patl->pat.ptr.reg);
		free(patl);
		return 0;
	}


	LIST_ADDQ(&expr->patterns, &patl->list);


	return 1;
}
