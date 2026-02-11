pdbioWriteText(AjPFile outf, const AjPStr str,
                             const char *prefix)
{
    ajint n = 0;
    ajint l = 0;
    ajint c = 0;

    AjPStrTok handle = NULL;
    AjPStr token = NULL;
    AjPStr tmp = NULL;

    if (!outf)
        return ajFalse;


    token = ajStrNew();
    tmp = ajStrNewC("");


    handle = ajStrTokenNewC(str, " \t\r\n");

    while (ajStrTokenNextParse(handle, &token))
    {
        if (!c)
            ajFmtPrintF(outf, "%-11s", prefix);

        if ((l = n + ajStrGetLen(token)) < 68)
        {
            if (c++)
                ajStrAppendC(&tmp, " ");
            ajStrAppendS(&tmp, token);
            n = ++l;
        }
        else
        {
            ajFmtPrintF(outf, "%-*S\n", 69, tmp);

            ajStrAssignS(&tmp, token);
            ajStrAppendC(&tmp, " ");
            n = ajStrGetLen(token);
            c = 0;
        }
    }

    if (c)
        ajFmtPrintF(outf, "%-*S\n", 69, tmp);


    ajStrTokenDel(&handle);
    ajStrDel(&token);
    ajStrDel(&tmp);

    return ajTrue;
}
