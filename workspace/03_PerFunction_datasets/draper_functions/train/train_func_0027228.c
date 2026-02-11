ffgrec( fitsfile *fptr,
            int nrec,
            char *card,
            int  *status)


{
    if (*status > 0)
        return(*status);

    if (nrec == 0)
    {
        ffmaky(fptr, 1, status);
        if (card)
            card[0] = '\0';
    }
    else if (nrec > 0)
    {
        ffmaky(fptr, nrec, status);
        ffgnky(fptr, card, status);
    }

    return(*status);
}
