comElabSeq(const char *seq,EmbPComUjwin ujwin,
                       ajint jmin, ajint jmax,
		       ajint lwin, ajint lseq,
		       ajint step)
{
    ajint j;
    ajint k = 0;
    ajint bwin;
    ajint ewin;
    ajint nwin = 0;
    char *wind;
    float Uj   = 0.0;

    AJCNEW(wind, lwin+1);

    bwin = 0;
    ewin = lwin-1;

    while(ewin<lseq)
    {
	nwin++;
	comReadWin(seq,bwin,ewin,wind);

	for(j=jmin;j<=jmax;j++)
	{
	    comCalcUj(lwin,j,wind,&Uj);
	    ujwin[nwin-1].Ujwin[k] = Uj;
	    k++;
	}

	bwin = bwin+step;
	ewin = bwin+(lwin-1);
	k = 0;
    }

    AJFREE(wind);

    return;
}
