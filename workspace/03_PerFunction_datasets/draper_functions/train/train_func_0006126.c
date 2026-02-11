ajFilenameReplaceExtC(AjPStr* Pfilename, const char* txt)
{
    AjBool doext;
    char *p = NULL;

    doext = ajTrue;
    if(!txt || !*txt)
        doext = ajFalse;


    ajStrAssignS(&fileTmpStr,*Pfilename);


    p = strrchr(ajStrGetuniquePtr(&fileTmpStr),SLASH_CHAR);

    if (!p)
        p = ajStrGetuniquePtr(&fileTmpStr);

    p = strrchr(p,'.');

    if(p)
    {
        *p='\0';
        fileTmpStr->Len = p - ajStrGetPtr(fileTmpStr);
    }


    if(doext)
    {
        ajStrAppendC(&fileTmpStr,".");
        ajStrAppendC(&fileTmpStr,txt);
    }

    ajStrAssignS(Pfilename,fileTmpStr);


    return ajTrue;
}
