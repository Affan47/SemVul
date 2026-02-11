fpregchk()
{
    reg_pt fpreg;

    fpreg_allowed = TRUE;
    fpreg = regchk();
    fpreg_allowed = FALSE;
    if (fpreg != ST0REG)
	return NOREG;
    getsym();
    if (sym == LPAREN)
    {
	getsym();
	if (sym != INTCONST || (unsigned) number >= 0x8)
	    error(ILL_FP_REG);
	else
	{
	    fpreg += number;
	    getsym();
	    if (sym != RPAREN)
		error(RPEXP);
	    else
		getsym();
	}
    }
    return fpreg;
}
