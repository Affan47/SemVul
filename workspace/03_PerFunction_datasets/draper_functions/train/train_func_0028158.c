ajFeatTypeMatchC(const AjPFeature gf, const char* txt)
{
    AjBool ret = ajFalse;
    AjPStr tmpstr;
    const AjPStr tmptype = NULL;

    if(ajStrMatchC(gf->Type, txt))
	return ajTrue;

    tmpstr = ajStrNewC(txt);

    if(gf->Protein)
    {
        tmptype = featTypeProtLimit(tmpstr);
        if(tmptype)
            ret = ajStrMatchS(featTypeProtLimit(gf->Type),
                              tmptype);
        ajDebug("ajFeatTypeMatch: %B '%S' prot: '%S' <=> '%S'\n",
                ret, tmpstr, tmptype, gf->Type);
    }

    else
    {
	tmptype = featTypeDnaLimit(tmpstr);
        if(tmptype)
            ret = ajStrMatchS(featTypeDnaLimit(gf->Type),
                              tmptype);
        ajDebug("ajFeatTypeMatch: %B '%S' dna: '%S' <=> '%S'\n",
                ret, tmpstr, tmptype, gf->Type);
    }

    ajStrDel(&tmpstr);

    return ret;
}
