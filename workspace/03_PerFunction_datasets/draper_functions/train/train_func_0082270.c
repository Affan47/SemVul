embPropProtGaps(AjPSeq seq, ajint pad)
{
    const char *p;
    AjPStr temp;
    ajint i;

    temp = ajStrNewRes(ajSeqGetLen(seq)*3 + pad+1);


    for(i=0; i<pad; i++)
	ajStrAppendC(&temp, " ");


    for(p=ajSeqGetSeqC(seq); *p; p++)
    {
	ajStrAppendK(&temp, *p);
	ajStrAppendC(&temp, "  ");
    }

    return temp;
}
