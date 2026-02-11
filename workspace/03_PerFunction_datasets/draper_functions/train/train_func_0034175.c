ajAlignDefineCC(AjPAlign thys, const char* seqa, const char* seqb,
		       const char* namea, const char* nameb)
{
    AlignPData data = NULL;

    AjPStr tmpstr = NULL;

    if(!thys->Nseqs)
	thys->Nseqs = 2;

    data = alignDataNew(2, AJFALSE);

    ajStrAssignC(&tmpstr, seqa);
    data->Start[0] = 1;
    data->End[0] = ajStrGetLen(tmpstr);
    data->Len[0] = ajStrGetLen(tmpstr) - ajSeqstrCountGaps(tmpstr);
    data->Offset[0] = 0;
    data->Offend[0] = 0;
    data->SubOffset[0] = 0;
    data->Rev[0] = ajFalse;


    data->RealSeq[0] = ajSeqNewNameC(seqa, namea);
    ajSeqGapStandard(data->RealSeq[0], '-');
    data->Seq[0] = data->RealSeq[0];

    ajStrAssignC(&tmpstr, seqb);
    data->Start[1] = 1;
    data->End[1] = ajStrGetLen(tmpstr);
    data->Len[1] = ajStrGetLen(tmpstr) - ajSeqstrCountGaps(tmpstr);
    data->Offset[1] = 0;
    data->Offend[1] = 0;
    data->SubOffset[1] = 0;
    data->Rev[1] = ajFalse;

    data->RealSeq[1] = ajSeqNewNameC(seqb, nameb);
    ajSeqGapStandard(data->RealSeq[1], '-');
    data->Seq[1] = data->RealSeq[1];

    data->LenAli = AJMIN(strlen(seqa), strlen(seqb));

    ajDebug("ajAlignDefineCC %s %d %s %d\n",
	    namea, ajSeqGetLen(data->Seq[0]),
	    nameb, ajSeqGetLen(data->Seq[1]));
    ajListPushAppend(thys->Data, data);

    ajStrDel(&tmpstr);

    return ajTrue;
}
