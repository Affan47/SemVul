seqWriteTreecon(AjPSeqout outseq)
{
    ajulong isize;
    ajuint ilen = 0;
    ajulong i    = 0;
    void** seqs = NULL;
    AjPSeq seq;
    AjPSeq* seqarr;
    ajulong itest;
    AjPStr sseq = NULL;

    ajDebug("seqWriteTreecon list size %Lu\n",
            ajListGetLength(outseq->Savelist));

    isize = ajListGetLength(outseq->Savelist);

    if(!isize)
	return;

    itest = ajListToarray(outseq->Savelist, (void***) &seqs);
    ajDebug("ajListToarray listed %Lu items\n", itest);
    seqarr = (AjPSeq*) seqs;

    for(i=0UL; i < isize; i++)
    {
	seq = seqarr[i];

	if(ilen < ajSeqGetLen(seq))
	    ilen = ajSeqGetLen(seq);
    }

    ajFmtPrintF(outseq->File,
		"%d\n", ilen);

    for(i=0; i < isize; i++)
    {

	seq = seqarr[i];
	ajStrAssignS(&sseq, seq->Seq);
	ajSeqGapS(&sseq, '-');
	ajFmtPrintF(outseq->File,
		    "%S\n%S\n",
		    seq->Name, sseq);
    }

    ajStrDel(&sseq);
    AJFREE(seqs);

    return;
}
