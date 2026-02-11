ajAcdIsUserdefinedC(const char *token)
{
    AcdPAcd acd;
    ajint pnum = 0;
    AjPStr tmpstr = NULL;

    tmpstr = ajStrNewC(token);

    acdTokenToLowerS(&tmpstr, &pnum);

    acd = acdFindAcd(tmpstr, tmpstr);

    if(!acd)
    {
        ajErr("Qualifier '-%s' not found", token);
        return ajFalse;
    }

    ajStrDel(&tmpstr);

    return acd->UserDefined;
}
