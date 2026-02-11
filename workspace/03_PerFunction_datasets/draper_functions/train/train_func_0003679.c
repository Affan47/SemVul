ffgidt( fitsfile *fptr,
            int  *imgtype,
            int  *status)


{
    if (*status > 0)
        return(*status);


    if (fptr->HDUposition != (fptr->Fptr)->curhdu)
        ffmahd(fptr, (fptr->HDUposition) + 1, NULL, status);
    else if ((fptr->Fptr)->datastart == DATA_UNDEFINED)
        if ( ffrdef(fptr, status) > 0)
            return(*status);


    ffmaky(fptr, 1, status);

    if ((fptr->Fptr)->hdutype == IMAGE_HDU)
    {
        ffgky(fptr, TINT, "BITPIX", imgtype, NULL, status);
    }
    else if ((fptr->Fptr)->compressimg)
    {

        ffgky(fptr, TINT, "ZBITPIX", imgtype, NULL, status);
    }
    else
    {
        *status = NOT_IMAGE;
    }

    return(*status);
}
