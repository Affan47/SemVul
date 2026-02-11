comComplexOnSeq2(const char *seq,
			     ajint lseq, ajint lwin,
			     ajint jmin, ajint jmax, ajint step,
			     float *ComplexOfSeq)
{
    ajint bwin;
    ajint ewin;
    ajint nwin;
    char *wind;
    float ComplexOfWin = 0.0;

    AJCNEW(wind, lwin+1);

    bwin = 0;
    ewin = lwin-1;
    nwin = 0;

    while(ewin<lseq)
    {
	comReadWin(seq,bwin,ewin,wind);
	comWinComplex2(wind,lwin,&ComplexOfWin,jmin,jmax);
	ComplexOfSeq[nwin] = ComplexOfWin;
	bwin = bwin+step;
	ewin = bwin+lwin-1;
	nwin++;
    }

    AJFREE(wind);

    return;
}
