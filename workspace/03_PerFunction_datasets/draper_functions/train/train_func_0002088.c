ajFeatGetSeq(const AjPFeature thys,
                    const AjPSeq seq, AjPStr* Pseqstr)
{
    AjPSeq remoteseq = NULL;

    AjPStr tmpseq = NULL;
    AjBool compjoin = ajFalse;

    ajStrSetClear(Pseqstr);


    ajDebug("ajFeatGetSeq usa:%S\n",
            ajSeqGetUsaS(seq));

    if(thys->Flags & AJFEATFLAG_BETWEEN_SEQ)
        return ajTrue;

    ajFeatTrace(thys);

    if(thys->Flags & AJFEATFLAG_REMOTEID)
    {
        if(!remoteseq)
            remoteseq = ajSeqNew();

        ajFeatGetRemoteseq(thys, ajSeqGetUsaS(seq), remoteseq);
        ajStrAppendS(Pseqstr, ajSeqGetSeqS(remoteseq));
    }
    else
    {
        if(thys->Strand == '-' && !compjoin)
        {
            ajStrAppendSubS(&tmpseq, ajSeqGetSeqS(seq),
                            ajFeatGetStart(thys)-1, ajFeatGetEnd(thys)-1);
            ajSeqstrReverse(&tmpseq);
            ajStrInsertS(Pseqstr, 0, tmpseq);
            ajStrDel(&tmpseq);
        }
        else
        {
            ajStrAppendSubS(Pseqstr, ajSeqGetSeqS(seq),
                            ajFeatGetStart(thys)-1, ajFeatGetEnd(thys)-1);
        }
    }

    ajSeqDel(&remoteseq);

    return ajTrue;
}
