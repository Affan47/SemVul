embIepPkReadFile(double **pK, AjPFile pkfile)
{
    AjPStr line;
    const char *p;
    double  amino    = 7.50;
    double  carboxyl = 3.55;
    double dval = 0.0;
    char ch;
    ajuint ich;
    ajuint i;
    ajuint j;

    if(!pkfile)
	ajFatal("%s file not found",PKFILE);

    for(j=0; j < 3; ++j)
        for(i=0; i < EMBIEPSIZE; ++i)
            pK[i][j] = 0.0;

    line = ajStrNew();

    while(ajReadline(pkfile,&line))
    {
	p = ajStrGetPtr(line);

	if(*p=='#' || *p=='!' || *p=='\n' || *p=='\r')
	    continue;

	if(ajStrPrefixCaseC(line,"Amino"))
	{
	    p = ajSysFuncStrtok(p," \t\n\r");
	    p = ajSysFuncStrtok(NULL," \t\n\r");
	    sscanf(p,"%lf",&amino);
	    continue;
	}

	if(ajStrPrefixCaseC(line,"Carboxyl"))
	{
	    p = ajSysFuncStrtok(p," \t\n\r");
	    p = ajSysFuncStrtok(NULL," \t\n\r");
	    sscanf(p,"%lf",&carboxyl);
	    continue;
	}

	p  = ajSysFuncStrtok(p," \t\n\r");
	ch = ajSysCastItoc(toupper((ajint)*p));
        ich = ajBasecodeToInt(ch);

	p  = ajSysFuncStrtok(NULL," \t\n\r");
        sscanf(p, "%lf", &pK[ich][0]);

        p  = ajSysFuncStrtok(NULL," \t\n\r");

	if(p && sscanf(p, "%lf", &dval))
            pK[ich][1] = dval;
        else
            pK[ich][1] = 0.0;

        p  = ajSysFuncStrtok(NULL," \t\n\r");

	if(p && sscanf(p, "%lf", &dval))
            pK[ich][2] = dval;
        else
            pK[ich][2] = 0.0;
    }

    pK[EMBIEPAMINO][0]    = amino;
    pK[EMBIEPAMINO][1]    = amino;
    pK[EMBIEPCARBOXYL][0] = carboxyl;
    pK[EMBIEPCARBOXYL][2] = carboxyl;

    ajStrDel(&line);

    return;
}
