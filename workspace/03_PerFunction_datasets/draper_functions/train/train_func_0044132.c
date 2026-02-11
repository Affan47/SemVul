cbr_scan3(struct ast_private *ast)
{
	u32 patcnt, loop;

	for (patcnt = 0; patcnt < CBR_PATNUM; patcnt++) {
		ast_moutdwm(ast, 0x1e6e007c, pattern[patcnt]);
		for (loop = 0; loop < 2; loop++) {
			if (cbr_test3(ast))
				break;
		}
		if (loop == 2)
			return 0;
	}
	return 1;
}
