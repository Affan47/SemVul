ajFilebuffTraceFull(const AjPFilebuff buff, size_t nlines,
                         size_t nfree)
{
    ajint i;
    AjPFilebufflist line;
    AjBool last = ajFalse;

    ajDebug("Trace buffer file '%S' End: %B\n"
            "             Pos: %d Size: %d Nobuff: %B Fpos: %Ld\n",
            buff->File->Name, buff->File->End,
            buff->Pos, buff->Size, buff->Nobuff, buff->Fpos);

    line = buff->Lines;

    for(i=1; line && (i <= (ajint)nlines); i++)
    {
        if(line == buff->Curr)
            ajDebug("*Line %x %d: %5d %5d <%-20S>\n",
                    line->Line, i,
                    ajStrGetLen(line->Line), strlen(ajStrGetPtr(line->Line)),
                    line->Line);
        else
            ajDebug(" Line %x %d: %5d %5d <%-20S>\n",
                    line->Line, i,
                    ajStrGetLen(line->Line), strlen(ajStrGetPtr(line->Line)),
                    line->Line);
        line = line->Next;
    }

    line = buff->Freelines;

    for(i=1; line && (i <= (ajint)nfree);  i++)
    {
        if(line == buff->Freelast)
            last = ajTrue;

        ajDebug(" Free %x %d: %d bytes %B\n",
                line->Line, i, ajStrGetRes(line->Line), last);
        line = line->Next;
    }

    return;
}
