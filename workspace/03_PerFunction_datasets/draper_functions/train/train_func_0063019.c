ajMartDecodeHname(const AjPStr dir, AjPStr *host, AjPStr *path,
                       ajuint *port)
{
    AjPStr str = NULL;
    AjPStrTok handle = NULL;

    str = ajStrNew();

    handle = ajStrTokenNewC(dir, "+");

    if(!ajStrTokenNextParse(handle, &str))
    {
        ajErr("ajMartDecodeHname: Bad directory name [%S]",dir);
        return;
    }

    ajStrExchangeKK(&str,'%','.');
    ajStrAssignS(host,str);

    if(!ajStrTokenNextParse(handle, &str))
    {
        ajErr("ajMartDecodeHname: Bad directory name [%S]",dir);
        return;
    }

    ajStrExchangeKK(&str,'^','/');
    ajStrAssignS(path,str);

    if(!ajStrTokenNextParse(handle, &str))
    {
        ajErr("ajMartDecodeHname: Bad directory name [%S]",dir);
        return;
    }

    ajStrToUint(str,port);

    ajStrDel(&str);
    ajStrTokenDel(&handle);

    return;
}
