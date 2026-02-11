pilFitsHdrCount(PilFitsFile *fitsFile)
{

    int status = 0;
    int nHdu   = 0;

    if (fitsFile)
        if (!ffthdu(fitsFile->fptr, &nHdu, &status))
            return nHdu;

    return 0;

}
