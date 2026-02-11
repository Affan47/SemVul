ajFeattypeGetExternal(const AjPStr type,
                                   const AjPTable table)
{
    static const AjPStr ret = NULL;
    static const AjPStr retkey = NULL;
    AjPStr defaultid = NULL;
    AjPStr tmpstr = NULL;
    ajlong i;

    retkey = ajTablestrFetchkeyS(table, type);

    if(!retkey)
    {
        defaultid = ajStrNew();
        retkey = ajTableFetchS(table, defaultid);
        ajStrDel(&defaultid);
        ajDebug("ajFeattypeGetExternal '%S' not in external table %x, "
                "use default '%S'\n", type, table, retkey);
    }

    ret = ajTableFetchS(table, retkey);


    if(ajStrGetCharLast(ret) != ';')
    {
        retkey = ret;
        ret = ajTableFetchS(table, retkey);
        ajDebug("ajFeattypeGetExternal b '%S' found in internal table"
                " as '%S' = '%S\n", type, retkey, ret);
    }

    if(ajStrGetCharLast(ret) == ';')
    {
        if(ajStrGetCharFirst(ret) == ';')
        {
            ret = retkey;
        }
        else
        {
            i = ajStrFindAnyK(ret, ';');
            ajStrAssignSubS(&tmpstr, ret, 0, i-1);


            ret = ajTablestrFetchkeyS(table, tmpstr);

            if(!ret)
            {
                ajFeatWarn("ajFeattypeGetExternal failed to find"
                         " '%S' alias '%S",
                         type, tmpstr);
                ret = ajTableFetchS(table, retkey);
            }

            ajStrDel(&tmpstr);
        }
    }


    return ret;
}
