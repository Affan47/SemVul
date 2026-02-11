ajCodSetBacktranslate(AjPCod thys)
{
    ajint i;
    ajint aa;
    double f;
    double f2;

    if(!thys)
	ajFatal("Codon usage object uninitialised");

    for(i=0;i<AJCODAMINOS;++i)
	thys->back[i] = -1;

    for(i=0;i<AJCODSTART;++i)
    {
	aa = thys->aa[i];

	if(thys->back[aa]<0)
	    thys->back[aa] = i;

	f = thys->fraction[i];
	f2 = thys->fraction[thys->back[aa]];

	if(f>f2)
	    thys->back[aa] = i;
    }

    return;
}
