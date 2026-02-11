seqReadAcedb(AjPSeq thys, AjPSeqin seqin)
{
    AjPFilebuff buff;
    AjBool ok = ajTrue;

    ajDebug("seqReadAcedb\n");

    buff = seqin->Input->Filebuff;

    do
    {
        ok = ajTextinStoreReadline(seqin->Input, &seqReadLine, &thys->TextPtr);
    } while(ok &&
            (ajStrPrefixC(seqReadLine, "//") ||
             ajStrPrefixC(seqReadLine, "\n")));

    if(!ok)
    {
        ajTextinStoreReset(seqin->Input, &thys->TextPtr);

        return ajFalse;
    }

    ajDebug("first line:\n'%S'\n", seqReadLine);


    ajStrTokenAssignC(&seqHandle, seqReadLine, " \n\r");
    ajStrTokenNextParseC(seqHandle, " \t", &seqToken);
    ajDebug("Token 1 '%S'\n", seqToken);

    if(ajStrMatchCaseC(seqToken, "Peptide"))
    {
        ajDebug("Protein\n");
        ajSeqSetProt(thys);
    }
    else if(ajStrMatchCaseC(seqToken, "DNA"))
    {
        ajDebug("DNA\n");
        ajSeqSetNuc(thys);
    }
    else
    {
        ajDebug("unknown - failed\n");
        ajTextinStoreReset(seqin->Input, &thys->TextPtr);
        ajStrTokenReset(seqHandle);
        ajStrDelStatic(&seqToken);

        return ajFalse;
    }

    ajStrTokenNextParseC(seqHandle, " \t\"", &seqToken);

    if(!ajStrMatchC(seqToken, ":"))
    {
        ajTextinStoreReset(seqin->Input, &thys->TextPtr);
        ajStrTokenReset(seqHandle);
        ajStrDelStatic(&seqToken);

        return ajFalse;
    }

    ajStrTokenNextParseC(seqHandle, "\"", &seqToken);

    if(!ajStrGetLen(seqToken))
    {
        ajTextinStoreReset(seqin->Input, &thys->TextPtr);
        ajStrTokenReset(seqHandle);
        ajStrDelStatic(&seqToken);

        return ajFalse;
    }


    ajFilebuffSetUnbuffered(buff);

    seqSetName(thys, seqToken);


    ok = ajTextinStoreReadline(seqin->Input, &seqReadLine, &thys->TextPtr);
    while(ok && !ajStrPrefixC(seqReadLine,"\n"))
    {
        seqAppend(&thys->Seq, seqReadLine);
        ok = ajTextinStoreReadline(seqin->Input, &seqReadLine, &thys->TextPtr);
    }

    ajFilebuffClear(buff, 0);

    ajStrTokenReset(seqHandle);
    ajStrDelStatic(&seqToken);

    return ajTrue;
}
