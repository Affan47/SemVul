IsSGGFile(FileHelper * fh)
{
    fhReset(fh);
    fhSkipWS(fh);

    if (fhReadAnyAlphNumString(fh)) {
        fhSkipWS(fh);
        if (!fhReadString(fh, "vs."))
            return FALSE;
        fhSkipWS(fh);
        if (fhReadAnyAlphNumString(fh))
            return TRUE;
    }
    return FALSE;
}
