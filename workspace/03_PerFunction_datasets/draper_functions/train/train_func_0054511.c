edialign_init_seq(edialignCLOSURE *clos,
			      ajint nbreseq, ajint *longseq)
{
    ajint x;

    clos->seqNbr = nbreseq;

    clos->seq =
	(edialignSequence *) edialign_allouer(clos->seqNbr *
					      sizeof(edialignSequence));

    for (x=clos->maxLong=0; x < clos->seqNbr; x++)
    {
	clos->seq[x].longueur = longseq[x];
	if (clos->maxLong < longseq[x])
	    clos->maxLong = longseq[x];
    }

    return;
}
