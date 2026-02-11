ajCodGetCodonlist(const AjPCod cod, AjPList list)
{
    ajint i;
    ajint j;
    AjPStr codon = NULL;

    for(i=0;i<AJCODSTART;++i)
	for(j=0;j<cod->tcount[i];j++)
	{
	    codon = ajStrNewC(ajCodTriplet(i));
	    ajListstrPushAppend(list, codon);
	    codon = NULL;
	}

    return;
}
