ffmkyu(fitsfile *fptr,
           const char *keyname,
           const char *comm,
           int *status)
{
    char valstring[FLEN_VALUE];
    char oldcomm[FLEN_COMMENT];
    char card[FLEN_CARD];

    if (*status > 0)
        return(*status);

    if (ffgkey(fptr, keyname, valstring, oldcomm, status) > 0)
        return(*status);

    strcpy(valstring," ");

    if (!comm || comm[0] == '&')
        ffmkky(keyname, valstring, oldcomm, card, status);
    else
        ffmkky(keyname, valstring, comm, card, status);

    ffmkey(fptr, card, status);

    return(*status);
}
