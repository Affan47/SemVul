doelseif(func)
pfv func;
{
    if (iflevel == 0)
	error(ELSEIFBAD);
    else
    {
	ifflag = FALSE;
	if (elseflag)
	{
	    (*func) ();
	    if (!(lastexp.data & UNDBIT) && lastexp.offset != 0)

	    {
		ifflag = TRUE;
		elseflag = FALSE;
	    }
	}
	else
	{

	    while (sym != EOLSYM)
	        getsym();
	}
    }
}
