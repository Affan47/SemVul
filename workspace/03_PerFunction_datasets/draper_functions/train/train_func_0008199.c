antigenic_readAnti(AjPFloat *agp)
{
    AjPFile mfptr = NULL;
    AjPStr  line  = NULL;
    ajint Etot;
    ajint Stot;
    ajint Ptot;
    ajint n;

    ajint v1;
    ajint v2;
    ajint v3;
    float vf1;
    float vf2;
    float vf3;

    ajint deltae;
    ajint deltas;
    ajint deltap;
    float deltaaf;
    float deltasf;

    char *p;
    char *q;

    mfptr = ajDatafileNewInNameC(DATAFILE);
    if(!mfptr)
	ajFatal("Antigenicity file '%s' not found\n", DATAFILE);

    line=ajStrNew();

    deltae = deltas = deltap =0;
    deltaaf =deltasf = 0.0;

    while(ajReadline(mfptr, &line))
    {
	p = ajStrGetuniquePtr(&line);
	if(*p=='#' || *p=='!' || *p=='\n')
	    continue;

	if(strstr(p,"Total"))
	{
	    if(sscanf(p,"%*s%d%d%d",&Etot,&Stot,&Ptot) != 3)
		ajErr("Wrong number of fields in totals\n%s",
			ajStrGetPtr(line));
	    continue;
	}

	ajCharFmtUpper(p);
	q = p;
	q = ajSysFuncStrtok(q," \t");
	n = ajBasecodeToInt(*q);

	if(sscanf(p,"%*s%d%d%d%f%f%f",&v1,&v2,&v3,&vf1,&vf2,&vf3)!=6)
	{
	    ajErr("Error in table: %s",p);
	    embExitBad();
	}

	ajFloatPut(agp,n,vf3);

	if(*q != 'B' && *q != 'X' && *q != 'Z')
	{
	    deltae  += v1;
	    deltas  += v2;
	    deltap  += v3;
	    deltaaf += vf1;
	    deltasf += vf2;
	    if(fabs((double) (vf2-vf1 / vf3)) > 0.02)
		ajErr("propensity != afreq/sfreq in line\n%s",
		      p);
	}

    }


    if(deltae != Etot)
	ajErr("epitope total %d != total %d",Etot,
	      deltae);

    if(deltas != Stot)
	ajErr("surface total %d != total %d",Stot,
	      deltas);

    if(deltap != Ptot)
	ajErr("protein total %d != total %d",Ptot,
	      deltap);

    if(fabs((double) (1.0-deltaaf)) > 0.005)
	ajErr("afreq total %1.5f should be 1.0",deltaaf);

    if(fabs((double) (1.0-deltasf)) > 0.005)
	ajErr("sfreq total %1.5f should be 1.0",deltasf);


    ajStrDel(&line);
    ajFileClose(&mfptr);

    return;
}
