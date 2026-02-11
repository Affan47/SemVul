showdbDBWidth (const AjPStr dbname,
			   const AjPStr type, const AjPStr methods,
			   const AjPStr defined, const AjPStr release,
                           AjBool dofields, AjBool doaliases,
                           AjBool doexamples, AjBool dotaxons,
			   ajuint *maxname, ajuint* maxtype,
                           ajuint *maxmethod, ajuint *maxfield,
                           ajuint *maxalias, ajuint *maxexample,
                           ajuint *maxtax,
                           ajuint* maxdefined, ajuint *maxrelease)
{
    AjPStr fields = NULL;
    ajuint i;
    ajuint num;

    if (ajStrGetLen(dbname) > *maxname)
	*maxname = ajStrGetLen(dbname);

    if (ajStrGetLen(type) > *maxtype)
	*maxtype = ajStrGetLen(type);

    if (ajStrGetLen(methods) > *maxmethod)
	*maxmethod = ajStrGetLen(methods);

    if (ajStrGetLen(defined) > *maxdefined)
	*maxdefined = ajStrGetLen(defined);

    if (ajStrGetLen(release) > *maxrelease)
	*maxrelease = ajStrGetLen(release);

    if(dofields)
    {
        showdbGetFields(dbname, &fields, &num);
        i = ajStrGetLen(fields);
        if (i > *maxfield)
            *maxfield = i;
    }

    if(doaliases)
    {
        showdbGetAliases(dbname, &fields, &num);
        i = ajStrGetLen(fields);
        if (i > *maxalias)
            *maxalias = i;
    }

    if(doexamples)
    {
        showdbGetExamples(dbname, &fields, &num);
        i = ajStrGetLen(fields);
        if (i > *maxexample)
            *maxexample = i;
    }

    if(dotaxons)
    {
        showdbGetTaxons(dbname, &fields, &num);
        i = ajStrGetLen(fields);
        if (i > *maxtax)
            *maxtax = i;
    }

    ajStrDel(&fields);

    return;
}
