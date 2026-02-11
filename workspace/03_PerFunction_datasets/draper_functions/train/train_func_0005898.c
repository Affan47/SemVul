pimport()
{
    struct sym_s *symptr;

    if (binaryg)
	error(NOIMPORT);
    while (TRUE)
    {
	if ((symptr = needlabel()) != NUL_PTR && checksegrel(symptr))
	{
	    if (symptr->type & (COMMBIT | EXPBIT | LABIT))

		error(ALREADY);
	    else if( last_pass == 1 )

		symptr->data = lcdata | (FORBIT | IMPBIT | RELBIT);
	    else
		symptr->data = lcdata | (IMPBIT | RELBIT);
	}
	getsym();
	if (sym != COMMA)
	    break;
	getsym();
    }
}
