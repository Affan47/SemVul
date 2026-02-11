ffpdfl(fitsfile *fptr,
           int *status)


{
    char chfill, fill[2880];
    LONGLONG fillstart;
    int nfill, tstatus, ii;

    if (*status > 0)
        return(*status);

    if (fptr->HDUposition != (fptr->Fptr)->curhdu)
        return(*status);

    if ((fptr->Fptr)->heapstart == 0)
        return(*status);

    fillstart = (fptr->Fptr)->datastart + (fptr->Fptr)->heapstart +
                (fptr->Fptr)->heapsize;

    nfill = (long) ((fillstart + 2879) / 2880 * 2880 - fillstart);

    if ((fptr->Fptr)->hdutype == ASCII_TBL)
        chfill = 32;
    else
        chfill = 0;

    tstatus = 0;

    if (!nfill)
    {
        fillstart--;
        nfill = 1;
        ffmbyt(fptr, fillstart, REPORT_EOF, &tstatus);
        ffgbyt(fptr, nfill, fill, &tstatus);

        if (tstatus == 0)
            return(*status);
    }
    else
    {
        ffmbyt(fptr, fillstart, REPORT_EOF, &tstatus);
        ffgbyt(fptr, nfill, fill, &tstatus);

        if (tstatus == 0)
        {
            for (ii = 0; ii < nfill; ii++)
            {
                if (fill[ii] != chfill)
                    break;
            }

            if (ii == nfill)
                return(*status);
        }
    }


    memset(fill, chfill, nfill);

    ffmbyt(fptr, fillstart, IGNORE_EOF, status);
    ffpbyt(fptr, nfill, fill, status);

    if (*status > 0)
        ffpmsg("Error writing Data Unit fill bytes (ffpdfl).");

    return(*status);
}
