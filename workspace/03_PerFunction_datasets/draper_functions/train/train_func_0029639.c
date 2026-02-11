alignDataSetSequence(AlignPData thys, const AjPSeq seq, ajint iseq,
        AjBool external)
{
    if(external)
    {
        thys->Seq[iseq] = seq;
        return;
    }

    thys->Start[iseq] = ajSeqGetBegin(seq);
    thys->End[iseq]   = ajSeqGetEnd(seq);
    thys->Len[iseq]   = ajSeqGetLen(seq) + ajSeqGetOffset(seq)
                        + ajSeqGetOffend(seq) - ajSeqCountGaps(seq);
    thys->Offset[iseq] = ajSeqGetOffset(seq);
    thys->Offend[iseq] = ajSeqGetOffend(seq);
    thys->SubOffset[iseq] = 0;
    thys->Rev[iseq]    = ajSeqIsReversed(seq);

    thys->RealSeq[iseq] = ajSeqNewSeq(seq);
    ajSeqGapStandard(thys->RealSeq[iseq], '-');
    thys->Seq[iseq] = thys->RealSeq[iseq];

    return;
}
