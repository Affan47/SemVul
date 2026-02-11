embDbiFileOut(const AjPStr dbname, const char* extension)
{
    AjPFile ret;

    ajFmtPrintS(&dbiOutFname, "%S.%s", dbname, extension);
    ret = ajFileNewOutNameS(dbiOutFname);

    if(!ret)
	ajFatal("Cannot open %S for writing", dbiOutFname);

    return ret;
}
