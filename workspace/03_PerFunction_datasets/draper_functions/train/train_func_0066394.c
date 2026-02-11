ajAlignDefineSS(AjPAlign thys, const AjPSeq seqa, const AjPSeq seqb)
{
    AlignPData data = NULL;

    if(!thys->Nseqs)
	thys->Nseqs = 2;

    if(thys->Nseqs != 2)
    {
	ajErr("ajAlignDefineSS called with %d sequences in alignment",
	      thys->Nseqs);
    }

    data = alignDataNew(2, thys->SeqExternal);

    ajDebug("ajAlignDefineSS '%S' '%S'\n",
	    ajSeqGetNameS(seqa), ajSeqGetNameS(seqb));

    alignDataSetSequence(data, seqa, 0, thys->SeqExternal);

    if(!thys->SeqExternal && !ajSeqIsTrimmed(data->RealSeq[0]))
    {
	    ajSeqTrim(data->RealSeq[0]);
    }

    alignDataSetSequence(data, seqb, 1, thys->SeqExternal);

    if(!thys->SeqExternal && !ajSeqIsTrimmed(data->RealSeq[1]))
    {
	    ajSeqTrim(data->RealSeq[1]);
    }

    data->LenAli = AJMIN(ajSeqGetLen(seqa), ajSeqGetLen(seqb));

    ajListPushAppend(thys->Data, data);

    return ajTrue;
}
