textinQryProcess(AjPTextin textin, AjPText text)
{
    AjBool ret = ajTrue;
    AjPStr qrystr = NULL;
    AjBool nontextmethod = ajFalse;
    const AjPStr fmtstr = NULL;
    AjPQuery qry;

    qry = textin->Query;


    qrystr = ajStrNewS(textin->Qry);

    ajDebug("++textinQryProcess '%S' \n", qrystr);


    fmtstr = ajQuerystrParseFormat(&qrystr, textin, textinformatFind);
    ajDebug("textinQryProcess ... fmtstr '%S' '%S'\n", fmtstr, qrystr);


    if(ajQuerystrParseListfile(&qrystr))
    {
        ajDebug("textinQryProcess ... listfile '%S'\n", qrystr);
        ret = textinListProcess(textin, text, qrystr);
        ajStrDel(&qrystr);
        return ret;
    }


    ajDebug("textinQryProcess ... no listfile '%S'\n", qrystr);
    if(!ajQuerystrParseRead(&qrystr, textin, textinformatFind, &nontextmethod))
    {
        ajStrDel(&qrystr);
        return ajFalse;
    }

    textinFormatSet(textin, text);

    ajDebug("textinQryProcess ... read nontext: %B '%S'\n",
            nontextmethod, qrystr);
    ajStrDel(&qrystr);

    if(nontextmethod)
    {
        ajDebug("textinQryProcess ... call method '%S'\n", qry->Method);
        ajDebug("textinQryProcess ... textin format %d '%S'\n",
                textin->Format, textin->Formatstr);
        ajDebug("textinQryProcess ...  query format  '%S'\n",
                qry->Formatstr);


    }

    ajDebug("seqinUsaProcess text method '%S' success\n", qry->Method);

    return ajTrue;
}
