ajHttpUrlrefSplitUsername(AjPUrlref urli)
{
    const char *p   = NULL;
    const char *end = NULL;
    AjPStr userpass = NULL;
    AjPStr host = NULL;

    ajint len;

    if(!ajStrGetLen(urli->Host))
        return;

    if(!(end = strchr(ajStrGetPtr(urli->Host), (int)'@')))
        return;

    p = ajStrGetPtr(urli->Host);
    len = end - p;

    if(!len)
        return;

    userpass = ajStrNew();
    ajStrAssignSubC(&userpass, p, 0, end - p - 1);

    host = ajStrNew();
    ajStrAssignC(&host,end + 1);
    ajStrAssignS(&urli->Host,host);


    if(!(end = strchr(ajStrGetPtr(userpass), (int)':')))
    {
        ajStrAssignS(&urli->Username,userpass);
        ajStrDel(&userpass);
        ajStrDel(&host);

        return;
    }

    p = ajStrGetPtr(userpass);
    len = end - p;

    if(!len)
        ajWarn("ajHttpUrlrefSplitUsername: Missing username in URL [%S@%S]",
               userpass,host);
    else
        ajStrAssignSubC(&urli->Username,p,0,len - 1);

    ajStrAssignC(&urli->Password, end + 1);

    ajStrDel(&userpass);
    ajStrDel(&host);

    return;
}
