ajReportSetType(AjPReport thys,
		      const AjPFeattable ftable, const AjPSeq seq)
{
    ajDebug("ajReportSetType '%S' ft: '%S' sq: '%S'\n",
	    thys->Type, ftable->Type, seq->Type);

    if(ajStrGetLen(thys->Type))
	return;

    if(ajStrGetLen(ftable->Type))
    {
	ajStrAssignS(&thys->Type, ftable->Type);

	return;
    }

    if(seq && ajStrGetLen(seq->Type))
    {
	ajStrAssignS(&thys->Type, seq->Type);

	return;
    }

    return;
}
