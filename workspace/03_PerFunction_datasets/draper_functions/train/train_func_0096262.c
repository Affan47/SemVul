lbranch(backamount)
int backamount;
{
    mcount += defsize + 0x1;
    segadj();
    if (pass2)
    {
	reldata();
	if (!(lastexp.data & (RELBIT | UNDBIT)))
	{
	    lastexp.offset = lastexp.offset - lc - lcjump;
	    if ( last_pass<2 && backamount != 0x0 &&
	        !(lastexp.data & IMPBIT) &&
		lastexp.offset + backamount < 0x80 + backamount)
		warning(SHORTB);
	}
    }
}
