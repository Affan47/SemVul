vcc_IfStmt(struct vcc *tl)
{

	SkipToken(tl, T_IF);
	Fb(tl, 1, "if ");
	vcc_Conditional(tl);
	ERRCHK(tl);
	L(tl, vcc_Compound(tl));
	ERRCHK(tl);
	while (1) {
		switch (tl->t->tok) {
		case T_ELSE:
			vcc_NextToken(tl);
			if (tl->t->tok != T_IF) {
				Fb(tl, 1, "else\n");
				L(tl, vcc_Compound(tl));
				ERRCHK(tl);
				return;
			}

		case T_ELSEIF:
		case T_ELSIF:
			Fb(tl, 1, "else if ");
			vcc_NextToken(tl);
			vcc_Conditional(tl);
			ERRCHK(tl);
			L(tl, vcc_Compound(tl));
			ERRCHK(tl);
			break;
		default:
			C(tl, ";");
			return;
		}
	}
}
