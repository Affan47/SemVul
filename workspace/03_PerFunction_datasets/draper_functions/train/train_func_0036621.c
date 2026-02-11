ffdblk(fitsfile *fptr,
           long nblocks,
           int *status)


{
    char buffer[2880];
    int tstatus, ii;
    LONGLONG readpos, writepos;

    if (*status > 0 || nblocks <= 0)
        return(*status);

    tstatus = 0;


    readpos = (fptr->Fptr)->datastart +
                   (fptr->Fptr)->heapstart +
                   (fptr->Fptr)->heapsize;
    readpos = ((readpos + 2879) / 2880) * 2880;


    writepos = readpos - ((LONGLONG)nblocks * 2880);

    while ( !ffmbyt(fptr, readpos, REPORT_EOF, &tstatus) &&
            !ffgbyt(fptr, 2880L, buffer, &tstatus) )
    {
        ffmbyt(fptr, writepos, REPORT_EOF, status);
        ffpbyt(fptr, 2880L, buffer, status);

        if (*status > 0)
        {
           ffpmsg("Error deleting FITS blocks (ffdblk)");
           return(*status);
        }
        readpos  += 2880;
        writepos += 2880;
    }


    memset(buffer, 0, 2880);
    ffmbyt(fptr, writepos, REPORT_EOF, status);

    for (ii = 0; ii < nblocks; ii++)
        ffpbyt(fptr, 2880L, buffer, status);


    ffmbyt(fptr, writepos - 1, REPORT_EOF, status);


    fftrun(fptr, writepos, status);


    for (ii = (fptr->Fptr)->curhdu; ii <= (fptr->Fptr)->maxhdu; ii++)
         (fptr->Fptr)->headstart[ii + 1] -= ((LONGLONG)nblocks * 2880);

    return(*status);
}
