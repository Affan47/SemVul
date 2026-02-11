distmat_getSeq(const AjPSeqset seqset, ajint nseqs, ajint mlen,
			     ajint incr, ajint posn, ajint* len)
{
    ajint i;
    ajint j;
    ajint count;

    AjBool onetwo = ajFalse;
    const char*  pseqset;
    char** pseq;


    if(posn == 12)
    {
	onetwo = ajTrue;
	posn   = 0;
	incr   = 3;
    }

    *len = 0;
    for(j=posn;j<mlen;j+=incr)
    {
	*len+=1;
	if(onetwo) *len+=1;
    }

    AJCNEW(pseq,nseqs);
    for(i=0;i<nseqs;i++)
    {
	pseqset =  ajSeqsetGetseqSeqC(seqset,i);
	pseq[i] = ajCharNewRes(*len);

	count = 0;
	for(j=posn;j<mlen;j+=incr)
	{
	    strncpy(pseq[i]+count,pseqset+j,1);
	    count++;
	    if(onetwo)
	    {
		strncpy(pseq[i]+count,pseqset+j+1,1);
		count++;
	    }
	}
	ajDebug("SEQ %d: %s",i,pseq[i]);
    }

    return pseq;
}
