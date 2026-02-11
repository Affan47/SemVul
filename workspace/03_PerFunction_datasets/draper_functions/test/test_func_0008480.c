seqABIGetFlagW(AjPFile fp, ajlong flagLabel,
			     ajlong word, ajshort* val)
{
    ajint     flagNum = -1;
    ajint     i;
    ajlong Label;
    ajlong jval;
    ajlong indexO;
    ajint  INDEX_ENTRY_LENGTH;

    INDEX_ENTRY_LENGTH= 28;

    if(ajFileSeek(fp,26,SEEK_SET) ||
       (!seqABIReadInt4(fp, &indexO))) ajFatal("Error - in finding flag");

    do
    {
        flagNum++;

        if (ajFileSeek(fp, indexO+(flagNum*INDEX_ENTRY_LENGTH), SEEK_SET) != 0)
            return ajFalse;

        if (!seqABIReadInt4(fp, &Label))
            return ajFalse;
    }
    while (Label != (ajlong)flagLabel);


    for (i=2; i<word; i++)
        if (!seqABIReadInt4(fp, &jval))
	    return ajFalse;

    if (!seqABIReadInt2(fp, val))
	return ajFalse;

    return ajTrue;
}
