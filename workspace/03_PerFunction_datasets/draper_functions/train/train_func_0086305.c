ajMartCheckHeader(AjPSeqin seqin, AjPMartqinfo qinfo)
{
    AjPMartquery mq = NULL;

    AjPMartAttribute att = NULL;
    AjPFilebuff buff = NULL;
    AjPStr line = NULL;
    AjPStr *ret = NULL;

    AjPStr keyname  = NULL;
    AjPStr keydname = NULL;
    const AjPStr value    = NULL;

    AjPStrTok handle = NULL;
    AjPStr token     = NULL;


    ajulong nfields = 0;

    ajulong i;
    ajuint j;

    mq = ajMartGetMartqueryPtr(seqin);

    if(!mq)
        return NULL;

    if(!qinfo)
        return NULL;

    if(!qinfo->Hheader)
        return NULL;

    att = mq->Atts;
    if(!att)
        return NULL;

    buff = seqin->Input->Filebuff;

    if(!buff)
        return NULL;

    line = ajStrNew();

    if(!ajBuffreadLine(buff, &line))
    {
        ajStrDel(&line);
        return NULL;
    }

    nfields = ajStrCalcCountK(line,'\t');
    ++nfields;

    AJCNEW0(ret,nfields + 1);

    ret[nfields] = NULL;

    keyname  = ajStrNewC("name");
    keydname = ajStrNewC("displayName");

    ajStrTokenAssignC(&handle, line, "\t\n");
    token = ajStrNew();

    for(i = 0; i < nfields; ++i)
    {
        ret[i] = ajStrNew();

        ajStrTokenNextParseNoskip(handle,&token);

        for(j = 0; j < att->Natts; ++j)
        {
            value = ajTableFetchS(att->Attributes[j], keydname);

            if(ajStrMatchS(value,token))
            {
                value = ajTableFetchS(att->Attributes[j], keyname);
                ajStrAssignS(&ret[i],value);
                break;
            }
        }

        if(j == att->Natts)
            ajErr("ajMartCheckHeader: Cannot match column %S",token);
    }


    ajStrDel(&keyname);
    ajStrDel(&keydname);
    ajStrDel(&line);
    ajStrDel(&token);
    ajStrTokenDel(&handle);

    return ret;
}
