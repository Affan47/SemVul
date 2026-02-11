reldata()
{
    if ((lastexp.data ^ lcdata) & (IMPBIT | RELBIT | SEGM))
    {
	if ((lastexp.data ^ lcdata) & RELBIT)
	    showrelbad();
	else
	{
	    pcrflag = OBJ_R_MASK;
	    lastexp.data = (lcdata & ~SEGM) | lastexp.data | RELBIT;

	}
    }
    else
	lastexp.data = (lastexp.data | lcdata) & ~(RELBIT | SEGM);
}
