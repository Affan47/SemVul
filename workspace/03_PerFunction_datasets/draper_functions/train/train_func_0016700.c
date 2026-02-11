textObdaIdxName(ajulong ipos, TextPObdaFile fil)
{
    AjPStr token = NULL;
    AjPStrTok handle = NULL;

    textObdaFileSeek(fil, ipos);
    ajReadbinStrTrim(fil->File, (size_t) fil->RecSize, &textObdaName);

    if(ajStrParseCountC(textObdaName, "\t;") != 4)
    {
        ajErr("bad OBDA index record at %u in '%F'",
              ipos, fil->File);
        return NULL;
    }

    handle = ajStrTokenNewC(textObdaName, "\t;");

    ajStrTokenNextParse(handle, &textObdaTmpName);

    ajStrTokenDel(&handle);
    ajStrDel(&token);

    return textObdaTmpName;
}
