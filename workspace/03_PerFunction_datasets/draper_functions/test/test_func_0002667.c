ensGvtranscriptvariationNewIni(
    EnsPGvtranscriptvariationadaptor gvtva,
    ajuint identifier,
    EnsPTranscript transcript,
    EnsPGvvariationfeature gvvf,
    AjPStr translationallele,
    AjPStr gvctset,
    ajuint codingstart,
    ajuint codingend,
    ajuint transcriptstart,
    ajuint transcriptend,
    ajuint translationstart,
    ajuint translationend)
{
    register ajuint i = 0U;

    AjBool match = AJFALSE;

    AjPStr value = NULL;

    AjPStrTok token = NULL;

    EnsPGvtranscriptvariation gvtv = NULL;


    if (gvctset && ajStrGetLen(gvctset))
    {
        token = ajStrTokenNewC(gvctset, ",");
        value = ajStrNew();

        while (ajStrTokenNextParse(token, &value))
        {
            match = ajFalse;

            for (i = 0U; gvconsequenceKType[i]; i++)
                if (ajStrMatchCaseC(value, gvconsequenceKType[i]))
                    match = ajTrue;

            if (match == ajFalse)
                ajFatal("ensGvtranscriptvariationNewIni got invalid "
                        "consequence type '%S'.", value);
        }

        ajStrTokenDel(&token);
        ajStrDel(&value);
    }

    AJNEW0(gvtv);

    gvtv->Use                = 1U;
    gvtv->Identifier         = identifier;
    gvtv->Adaptor            = gvtva;
    gvtv->TranscriptObject   = ensTranscriptNewRef(transcript);
    gvtv->Gvvariationfeature = ensGvvariationfeatureNewRef(gvvf);
    gvtv->TranslationAllele  = ajStrNewRef(translationallele);
    gvtv->CodingStart        = codingstart;
    gvtv->CodingEnd          = codingend;
    gvtv->TranscriptStart    = transcriptstart;
    gvtv->TranscriptEnd      = transcriptend;
    gvtv->TranslationStart   = translationstart;
    gvtv->TranslationEnd     = translationend;
    gvtv->GvconsequenceTypes = ensGvconsequenceTypesFromSet(gvctset);

    return gvtv;
}
