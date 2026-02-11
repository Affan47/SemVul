ajFeatGetRemoteseq(const AjPFeature thys, const AjPStr usa,
                                AjPSeq seq)
{
    AjPStr baseusa = NULL;
    ajuint ilen;
    const AjPStr remoteid = NULL;

    remoteid = ajSeqtestIsSeqversion(thys->Remote);

    if(!remoteid)
        remoteid = thys->Remote;

    ajSeqUsaGetBase(usa, &baseusa);

    ajStrAppendK(&baseusa, ':');
    ajStrAppendS(&baseusa, remoteid);
    ajSeqGetFromUsa(baseusa, thys->Protein, seq);

    ilen = ajSeqGetLen(seq);

    if(thys->Strand == '-')
        ajSeqSetRangeRev(seq, ajFeatGetStart(thys), ajFeatGetEnd(thys));
    else
        ajSeqSetRange(seq, ajFeatGetStart(thys), ajFeatGetEnd(thys));

    ajSeqTrim(seq);

    ajDebug("ajFeatGetRemoteseq (%S) '%S' => '%S' %u %u..%u (%u)\n",
            thys->Remote, usa, baseusa, ilen,
            ajFeatGetStart(thys), ajFeatGetEnd(thys), ajSeqGetLen(seq));

    ajStrDel(&baseusa);

    return ajTrue;
}
