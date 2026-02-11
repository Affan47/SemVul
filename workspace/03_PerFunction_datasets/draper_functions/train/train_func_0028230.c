ffmbyt(fitsfile *fptr,
           LONGLONG bytepos,
           int err_mode,
           int *status)
{


    long record;

    if (*status > 0)
       return(*status);

    if (bytepos < 0)
        return(*status = NEG_FILE_POS);

    if (fptr->HDUposition != (fptr->Fptr)->curhdu)
        ffmahd(fptr, (fptr->HDUposition) + 1, NULL, status);

    record = (long) (bytepos / IOBUFLEN);


    if ( ((fptr->Fptr)->curbuf < 0) ||
         (record != (fptr->Fptr)->bufrecnum[(fptr->Fptr)->curbuf]))
        ffldrc(fptr, record, err_mode, status);

    if (*status <= 0)
        (fptr->Fptr)->bytepos = bytepos;

    return(*status);
}
