patternSeqFormat(const AjPStr fmt)
{
    ajuint i = 0;

    if(!ajStrGetLen(fmt))
       return 0;

    while (patSeqInformat[i].Name)
    {
	if(ajStrMatchCaseC(fmt, patSeqInformat[i].Name))
	    return i;

	i++;
    }

    ajErr("Unrecognized pattern file format '%S'",fmt);

    return 0;
}
