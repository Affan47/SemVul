seqWriteFastqIllumina(AjPSeqout outseq)
{
    ajuint j;
    ajuint ilen;
    AjPStr seq = NULL;
    ajint  qchar;

    ajDebug("seqWriteFastqIllumina Name '%S'\n",
	    outseq->Name);

    seqDbName(&outseq->Name, outseq->Setoutdb);

    ajWritebinByte(outseq->File, '@');
    ajWriteline(outseq->File, outseq->Name);

    if(ajStrGetLen(outseq->Sv))
	ajWritelineSpace(outseq->File, outseq->Sv);
    else if(ajStrGetLen(outseq->Acc))
	ajWritelineSpace(outseq->File, outseq->Acc);


    if(ajStrGetLen(outseq->Desc))
       ajWritelineSpace(outseq->File, outseq->Desc);

    ajWritebinNewline(outseq->File);
    ilen = ajStrGetLen(outseq->Seq);

    ajWritelineNewline(outseq->File, outseq->Seq);
    ajWritebinByte(outseq->File, '+');
    ajWritebinNewline(outseq->File);

    ilen = ajStrGetLen(outseq->Seq);

    if(outseq->Accuracy)
    {
        ajStrAssignClear(&seq);

        for(j=0;j<ilen;j++)
        {
            qchar = 64 + (int) (0.5 + outseq->Accuracy[j]);
            if(qchar > 126)
                qchar = 126;
            else if(qchar < 33)
                qchar = 33;
            ajStrAppendK(&seq, (char) qchar);
        }

	ajWritelineNewline(outseq->File, seq);
    }

    else
    {


        ajStrAssignClear(&seq);

        ajStrAppendCountK(&seq,'A', ilen);

	ajWritelineNewline(outseq->File, seq);
    }

    ajStrDel(&seq);

    return;
}
