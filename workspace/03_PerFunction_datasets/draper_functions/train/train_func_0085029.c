FindUniqueSatellite(Pointer p, G_Synset ss)
{
    G_Synset slite;
    Synonym syn;

    for (slite = ss->fans; slite; slite = slite->ssnext)
	for (syn = slite->syns; syn; syn = syn->synnext)
	    if ((p->pslite == syn->word) &&
		(p->pslite_sense == syn->sensenum))
		return(syn);
    return(NULL);
}
