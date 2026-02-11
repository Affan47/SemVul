ajFeatTypeMatchS(const AjPFeature gf, const AjPStr str)
{
    AjBool ret = ajFalse;

    if(ajStrMatchS(gf->Type, str))
	return ajTrue;

    if(gf->Protein)
    {
	ret =   ajStrMatchS(featTypeProtLimit(gf->Type),featTypeProtLimit(str));
        ajDebug("ajFeatTypeMatch: %B '%S' '%S' prot: '%S' <=> '%S'\n",
                ret, str, gf->Type,
                featTypeProtLimit(str), featTypeProtLimit(gf->Type));
    }

    else
    {
	ret =   ajStrMatchS(featTypeDnaLimit(gf->Type),featTypeDnaLimit(str));
        ajDebug("ajFeatTypeMatch: %B '%S' '%S' dna: '%S' <=> '%S'\n",
                ret, str, gf->Type,
                featTypeDnaLimit(str), featTypeDnaLimit(gf->Type));
    }

    return ret;
}
