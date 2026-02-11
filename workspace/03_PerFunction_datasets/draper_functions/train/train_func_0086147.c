ajHttpUrlDeconstruct(const AjPStr url, ajint* iport, AjPStr* host,
                          AjPStr* urlget)
{
    AjPUrlref uo = NULL;

    uo = ajHttpUrlrefNew();

    ajHttpUrlrefParseC(&uo, ajStrGetPtr(url));
    ajHttpUrlrefSplitPort(uo);

    ajStrAssignS(host,uo->Host);
    ajFmtPrintS(urlget,"/%S",uo->Absolute);

    if(ajStrGetLen(uo->Port))
        ajStrToInt(uo->Port,iport);

    ajHttpUrlrefDel(&uo);

    return;
}
