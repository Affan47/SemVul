same_expr(expptr e1, expptr e2)
#endif
{
    if (!e1 || !e2)
	return !e1 && !e2;

    if (e1 -> tag != e2 -> tag || e1 -> headblock.vtype != e2 -> headblock.vtype)
	return 0;

    switch (e1 -> tag) {
        case TEXPR:
	    if (e1 -> exprblock.opcode != e2 -> exprblock.opcode)
		return 0;

	    return same_expr (e1 -> exprblock.leftp, e2 -> exprblock.leftp) &&
		   same_expr (e1 -> exprblock.rightp, e2 -> exprblock.rightp);
	case TNAME:
	case TADDR:
	    return same_ident (e1, e2);
	case TCONST:
	    return sameconst(&e1->constblock, &e2->constblock);
	default:
	    return 0;
    }
}
