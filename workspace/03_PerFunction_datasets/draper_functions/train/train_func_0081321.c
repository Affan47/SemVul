parse_error(struct vcc *tl)
{

	vcc_NextToken(tl);
	Fb(tl, 1, "VRT_error(sp,\n");
	if (tl->t->tok == '(') {
		vcc_NextToken(tl);
		vcc_Expr(tl, INT);
		if (tl->t->tok == ',') {
			Fb(tl, 1, ",\n");
			vcc_NextToken(tl);
			vcc_Expr(tl, STRING);
		} else
			Fb(tl, 1, ", 0\n");
		SkipToken(tl, ')');
	} else {
		vcc_Expr(tl, INT);
		if (tl->t->tok != ';') {
			Fb(tl, 1, ",\n");
			vcc_Expr(tl, STRING);
		} else
			Fb(tl, 1, ", 0\n");
	}
	Fb(tl, 1, ");\n");
	Fb(tl, 1, "VRT_done(sp, VCL_RET_ERROR);\n");
}
