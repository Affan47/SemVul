antigenic_dumptoFeat(ajint nhits, const AjPUint hp,
				 const AjPUint hpos, const AjPUint hlen,
				 const AjPFloat thisap, const AjPFloat hwt,
				 AjPFeattabOut featout, const char *seqname,
				 ajint begin)
{
    AjPFeattable feattable;
    AjPStr name   = NULL;
    float score   = 0.0;
    AjPStr source = NULL;
    AjPStr type   = NULL;
    AjPStr tag    = NULL;
    AjPStr val    = NULL;
    char strand   ='+';
    ajint frame   = 0;
    ajint i = 0;
    ajint k = 0;
    ajuint m = 0;
    ajuint iend;
    ajuint istart;
    ajint new;
    AjPFeature feature;

    name   = ajStrNew();
    source = ajStrNew();
    type   = ajStrNew();
    tag    = ajStrNew();
    score  = 0.0;


    val    = ajStrNew();
    name   = ajStrNew();
    source = ajStrNew();
    type   = ajStrNew();
    tag    = ajStrNew();


    ajStrAssignC(&name,seqname);

    feattable = ajFeattableNewProt(name);

    ajStrAssignC(&source,"antigenic");
    ajStrAssignC(&type,"misc_feature");

    ajStrAssignC(&tag,"note");

    for(i=nhits-1;i>-1;--i)
    {
	k = ajUintGet(hp,i);

	istart = ajUintGet(hpos,k);

	iend = istart + ajUintGet(hlen,k)-1;

	score = ajFloatGet(hwt,k);
	feature = ajFeatNew(feattable, source, type,
			    istart+begin, iend+begin,
			    score, strand, frame) ;

	new = 0;
	for(m=istart;m<=iend;++m)
	    if(ajFloatGet(thisap,m) == ajFloatGet(hwt,k))
	    {
		if(!new)
		{
		    ajFmtPrintS(&val,"max score at %d",m);
		    ajFeatTagSet(feature,tag,val);
		    new++;
		}
		else
		{
		    ajFmtPrintS(&val,",%d",m);
		    ajFeatTagSet(feature,tag,val);
		}
	    }
    }

    ajFeatSortByStart(feattable);
    ajFeattableWrite(featout, feattable);

    ajFeattableDel(&feattable);

    ajStrDel(&name);
    ajStrDel(&source);
    ajStrDel(&type);
    ajStrDel(&tag);
    ajStrDel(&val);

    return;
}
