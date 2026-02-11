asseminQryProcess(AjPAssemin assemin, AjPAssem assem)
{
    AjBool ret = ajTrue;
    AjPStr qrystr = NULL;
    AjBool assemmethod = ajFalse;
    const AjPStr fmtstr = NULL;
    AjPTextin textin;
    AjPQuery qry;
    AjPAssemAccess assemaccess = NULL;
    AjBool foo;

    textin = assemin->Input;
    qry = textin->Query;


    qrystr = ajStrNewS(textin->Qry);

    ajDebug("asseminQryProcess '%S'\n", qrystr);


    fmtstr = ajQuerystrParseFormat(&qrystr, textin, asseminformatFind);
    ajDebug("asseminQryProcess ... fmtstr '%S' '%S'\n", fmtstr, qrystr);


    ajQuerystrParseRange(&qrystr, &assemin->cbegin, &assemin->cend, &foo);


    if(ajQuerystrParseListfile(&qrystr))
    {
        ajDebug("asseminQryProcess ... listfile '%S'\n", qrystr);
        ret = asseminListProcess(assemin, assem, qrystr);
        ajStrDel(&qrystr);
        return ret;
    }


    ajDebug("asseminQryProcess ... no listfile '%S'\n", qrystr);
    if(!ajQuerystrParseRead(&qrystr, textin, asseminformatFind, &assemmethod))
    {
        ajStrDel(&qrystr);
        return ajFalse;
    }

    asseminFormatSet(assemin, assem);

    ajDebug("asseminQryProcess ... read nontext: %B '%S'\n",
            assemmethod, qrystr);
    ajStrDel(&qrystr);


    if(assemmethod)
    {
        ajDebug("asseminQryProcess ... call method '%S'\n", qry->Method);
        ajDebug("asseminQryProcess ... textin format %d '%S'\n",
                textin->Format, textin->Formatstr);
        ajDebug("asseminQryProcess ...  query format  '%S'\n",
                qry->Formatstr);
        qry->Access = ajCallTableGetS(assemDbMethods,qry->Method);
        assemaccess = qry->Access;
        return (*assemaccess->Access)(assemin);
    }

    ajDebug("asseminQryProcess text method '%S' success\n", qry->Method);

    return ajTrue;
}
