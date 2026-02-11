vcc_Conditional(struct vcc *tl)
{

	SkipToken(tl, '(');
	Fb(tl, 0, "(\n");
	L(tl, vcc_Expr(tl, BOOL));
	ERRCHK(tl);
	Fb(tl, 1, ")\n");
	SkipToken(tl, ')');
}
