seqWriteIg(AjPSeqout outseq)
{
    static SeqPSeqFormat sf = NULL;

    if(ajStrGetCharFirst(outseq->Type) == 'P')
            ajFmtPrintF(outseq->File, ";%S, %d aa\n",
                        outseq->Desc, ajStrGetLen(outseq->Seq));
        else
            ajFmtPrintF(outseq->File, ";%S, %d bases\n",
			outseq->Desc, ajStrGetLen(outseq->Seq));

    ajWritelineNewline(outseq->File, outseq->Name);

    seqSeqFormat(ajStrGetLen(outseq->Seq), &sf);
    strcpy(sf->endstr, "1");

    seqWriteSeq(outseq, sf);
    seqFormatDel(&sf);

    return;
}
