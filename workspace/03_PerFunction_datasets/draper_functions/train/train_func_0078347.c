ajFeattableNewSeq(const AjPSeq seq)
{
    AjPFeattable thys = NULL;


    if(ajSeqIsProt(seq))
	thys = ajFeattableNewProt(ajSeqGetNameS(seq));
    else
	thys = ajFeattableNewDna(ajSeqGetNameS(seq));

    thys->Len = ajSeqGetLen(seq);

    return thys;
}
