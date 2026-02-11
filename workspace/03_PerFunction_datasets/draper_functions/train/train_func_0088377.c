ffucrd(fitsfile *fptr,
           const char *keyname,
           const char *card,
           int *status)
{
    int tstatus;

    if (*status > 0)
        return(*status);

    tstatus = *status;

    if (ffmcrd(fptr, keyname, card, status) == KEY_NO_EXIST)
    {
        *status = tstatus;
        ffprec(fptr, card, status);
    }
    return(*status);
}
