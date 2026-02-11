pilFitsHdrInsertCard(PilFitsFile *fitsFile, int before,
                         const char *refKeyName, const char *card)
{

    int  status = 0;
    int  countKeys = 0;
    int  position = 0;
    char dummy[FLEN_CARD];


    if (!fitsFile)
        return EXIT_FAILURE;

    ffgrec(fitsFile->fptr, 0, dummy, &status);
    ffgnxk(fitsFile->fptr, (char **)&refKeyName, 1, NULL, 0, dummy, &status);
    ffghps(fitsFile->fptr, &countKeys, &position, &status);

    if (before) {


        position--;
        ffgrec(fitsFile->fptr, position, dummy, &status);

    }

    ffirec(fitsFile->fptr, position, (char *)card, &status);

    if (status)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;

}
