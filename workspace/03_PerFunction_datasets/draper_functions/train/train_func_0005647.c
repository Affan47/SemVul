ffgtbb(fitsfile *fptr,
           LONGLONG firstrow,
           LONGLONG firstchar,
           LONGLONG nchars,
           unsigned char *values,
           int *status)


{
    LONGLONG bytepos, endrow;

    if (*status > 0 || nchars <= 0)
        return(*status);

    else if (firstrow < 1)
        return(*status=BAD_ROW_NUM);

    else if (firstchar < 1)
        return(*status=BAD_ELEM_NUM);

    if (fptr->HDUposition != (fptr->Fptr)->curhdu)
        ffmahd(fptr, (fptr->HDUposition) + 1, NULL, status);


    endrow = ((firstchar + nchars - 2) / (fptr->Fptr)->rowlength) + firstrow;
    if (endrow > (fptr->Fptr)->numrows)
    {
        ffpmsg("attempt to read past end of table (ffgtbb)");
        return(*status=BAD_ROW_NUM);
    }


    bytepos = (fptr->Fptr)->datastart +
              ((fptr->Fptr)->rowlength * (firstrow - 1)) +
              firstchar - 1;

    ffmbyt(fptr, bytepos, REPORT_EOF, status);
    ffgbyt(fptr, nchars, values, status);

    return(*status);
}
