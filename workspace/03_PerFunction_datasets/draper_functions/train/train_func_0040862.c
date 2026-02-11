urlinReadHtml(AjPUrlin urlin, AjPUrl url)
{
    AjPFilebuff buff;

    ajlong fpos     = 0;
    ajuint linecnt = 0;

    ajDebug("urlinReadHtml\n");
    ajUrlClear(url);
    buff = urlin->Input->Filebuff;


    while (ajBuffreadLinePos(buff, &urlinReadLine, &fpos))
    {
        linecnt++;

        if(ajStrGetCharLast(urlinReadLine) == '\n')
            ajStrCutEnd(&urlinReadLine, 1);

        if(ajStrGetCharLast(urlinReadLine) == '\r')
            ajStrCutEnd(&urlinReadLine, 1);

        ajDebug("line %u:%S\n", linecnt, urlinReadLine);


    }

    return ajTrue;
}
