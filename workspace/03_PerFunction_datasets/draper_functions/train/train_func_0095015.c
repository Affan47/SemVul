textObdaSecQuery(AjPQuery qry, const AjPStr field,
                               const AjPStr wildqry)
{
    ajint ret=0;

    if(ajStrMatchC(field, "org"))
	ret += textObdaSecFind(qry, "taxon", wildqry);

    if(ajStrMatchC(field, "key"))
	ret += textObdaSecFind(qry, "keyword", wildqry);

    if(ajStrMatchC(field, "des"))
	ret += textObdaSecFind(qry, "des", wildqry);

    if(ajStrMatchC(field, "sv"))
	ret += textObdaSecFind(qry, "seqvn", wildqry);

    if(ajStrMatchC(field, "gi"))
	ret += textObdaSecFind(qry, "gi", wildqry);

    if(qry->HasAcc && ajStrMatchC(field, "acc"))
	ret += textObdaSecFind(qry, "ACC", wildqry);


    if(ret)
	return ajTrue;

    return ajFalse;
}
