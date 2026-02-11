seqUsaRegInit(void)
{
    if(seqRegUsaInitDone)
        return;

    if(!seqRegUsaFmt)
        seqRegUsaFmt = ajRegCompC("^([A-Za-z0-9-]*)::(.*)$");


    if(!seqRegUsaDb)
        seqRegUsaDb = ajRegCompC("^([A-Za-z][A-Za-z0-9_]+)([-]([A-Za-z]+))?"
                                 "([:{]([^}]*)}?)?$");


    if(!seqRegUsaId)
#ifndef WIN32

        seqRegUsaId = ajRegCompC("^([^|]+[|]|[^:{%]+)"
                                 "(([:{%])(([^:}]+):)?([^:}]*)}?)?$");
#else


    seqRegUsaId = ajRegCompC ("^(([a-zA-Z]:[\\\\/])?[^:{%]+)"
                              "(([:{%])(([^:}]+):)?([^:}]*)}?)?$");
#endif


    if(!seqRegUsaList)
        seqRegUsaList = ajRegCompC("^(@|[Ll][Ii][Ss][Tt]:+)(.+)$");

    if(!seqRegUsaAsis)
        seqRegUsaAsis = ajRegCompC("^[Aa][Ss][Ii][Ss]:+(.+)$");

    if(!seqRegUsaWild)
        seqRegUsaWild = ajRegCompC("(.*[*].*)");


    if(!seqRegUsaRange)
        seqRegUsaRange = ajRegCompC("(.*)[[](-?[0-9]*):(-?[0-9]*)(:([Rr])?)?[]]$");

    seqRegUsaInitDone = ajTrue;

    return;
}
