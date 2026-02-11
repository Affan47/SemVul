ajFilenameTrimPath(AjPStr* Pfilename)
{
    ajlong i;

    if(!ajStrGetLen(*Pfilename))
        return ajFalse;

    i = ajStrFindlastC(*Pfilename, SLASH_STRING);

    if(i < 0)
        return ajFalse;

    ajStrCutStart(Pfilename, (size_t) (i+1));

    return ajTrue;
}
