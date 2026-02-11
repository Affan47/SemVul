ffdtdm(fitsfile *fptr,
           char *tdimstr,
           int colnum,
           int maxdim,
           int *naxis,
           long naxes[],
           int *status)


{
    long dimsize, totalpix = 1;
    char *loc, *lastloc, message[81];
    tcolumn *colptr;

    if (*status > 0)
        return(*status);

    if (fptr->HDUposition != (fptr->Fptr)->curhdu)
        ffmahd(fptr, (fptr->HDUposition) + 1, NULL, status);

    if (colnum < 1 || colnum > (fptr->Fptr)->tfield)
        return(*status = BAD_COL_NUM);

    colptr = (fptr->Fptr)->tableptr;
    colptr += (colnum - 1);

    if (!tdimstr[0])
    {
        *naxis = 1;
        if (maxdim > 0)
            naxes[0] = (long) colptr->trepeat;
    }
    else
    {
        *naxis = 0;

        loc = strchr(tdimstr, '(' );
        if (!loc)
        {
            sprintf(message, "Illegal TDIM keyword value: %s", tdimstr);
            return(*status = BAD_TDIM);
        }

        while (loc)
        {
            loc++;
            dimsize = strtol(loc, &loc, 10);
            if (*naxis < maxdim)
                naxes[*naxis] = dimsize;

            if (dimsize < 0)
            {
                ffpmsg("one or more TDIM values are less than 0 (ffdtdm)");
                ffpmsg(tdimstr);
                return(*status = BAD_TDIM);
            }

            totalpix *= dimsize;
            (*naxis)++;
            lastloc = loc;
            loc = strchr(loc, ',');
        }

        loc = strchr(lastloc, ')' );
        if (!loc)
        {
            sprintf(message, "Illegal TDIM keyword value: %s", tdimstr);
            return(*status = BAD_TDIM);
        }

        if ((colptr->tdatatype > 0) && ((long) colptr->trepeat != totalpix))
        {
          sprintf(message,
          "column vector length, %ld, does not equal TDIMn array size, %ld",
          (long) colptr->trepeat, totalpix);
          ffpmsg(message);
          ffpmsg(tdimstr);
          return(*status = BAD_TDIM);
        }
    }
    return(*status);
}
