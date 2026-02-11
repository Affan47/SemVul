newcpgreport_reportislands(AjPFile outf,const  AjBool *thresh,
				       const char *bases, const char *name,
				       float minobsexp, float minpc,
				       ajint minlen, ajint begin,
				       ajint len, const char *seq)
{
    AjBool island;
    ajint startpos = 0;
    ajint endpos;
    ajint slen;
    ajint i;
    ajint cnt = 0;

    ajFmtPrintF(outf,"ID   %s  %d BP.\n",name, len);
    ajFmtPrintF(outf,"XX\n");
    ajFmtPrintF(outf,"DE   CpG Island report.\n");
    ajFmtPrintF(outf,"XX\n");
    ajFmtPrintF(outf,"CC   Obs/Exp ratio > %.2f.\n",minobsexp);
    ajFmtPrintF(outf,"CC   %% %c + %% %c > %.2f.\n",bases[0],
		bases[1],minpc);
    ajFmtPrintF(outf,"CC   Length > %d.\n",minlen);
    ajFmtPrintF(outf,"XX\n");
    ajFmtPrintF(outf,"FH   Key              Location/Qualifiers\n");


    island = ajFalse;
    for(i=0;i<len;++i)
    {
	if(island)
	{
	    island = thresh[i];
	    if(!island)
	    {
	       slen = i - startpos;
		endpos = i;
		ajFmtPrintF(outf,"FT   CpG island       %d..%d\n",
			    startpos+begin+1, endpos+begin);
		ajFmtPrintF(outf,"FT                    /size=%d\n",
			    slen);
		newcpgreport_compisl(outf, seq, startpos+begin+1,
				     endpos+begin);
		++cnt;

	    }
	}
	else
	{
	    island = thresh[i];
	    if(island)
		startpos=i;

	}
    }

    if(island)
    {
        slen   = len-startpos+1;
	endpos = len-1;
       	ajFmtPrintF(outf,"FT   CpG island       %d..%d\n",
			    startpos+begin+1, endpos+begin);
        ajFmtPrintF(outf,"FT                    /size=%d\n",
		    slen);
	newcpgreport_compisl(outf, seq, startpos+begin+1, endpos+begin);
	++cnt;
    }

    if(cnt < 1)
	ajFmtPrintF(outf,"FT   no islands detected\n");
    else
	ajFmtPrintF(outf,"FT   numislands       %d\n",cnt);

    ajFmtPrintF(outf,"//\n");


    return;
}
