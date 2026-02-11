ajFilenameReplacePathS(AjPStr* Pfilename, const AjPStr str)
{
    if(!ajStrGetLen(str))
        return ajFalse;

    return ajFilenameReplacePathC(Pfilename, ajStrGetPtr(str));
}
