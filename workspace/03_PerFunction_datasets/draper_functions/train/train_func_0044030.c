ffpdes(fitsfile *fptr,
           int colnum,
           LONGLONG rownum,
           LONGLONG length,
           LONGLONG heapaddr,
           int *status)


{
    LONGLONG bytepos;
    unsigned int descript4[2];
    LONGLONG descript8[2];
    tcolumn *colptr;

    if (*status > 0)
        return(*status);


    if (fptr->HDUposition != (fptr->Fptr)->curhdu)
        ffmahd(fptr, (fptr->HDUposition) + 1, NULL, status);
    else if ((fptr->Fptr)->datastart == DATA_UNDEFINED)
        if ( ffrdef(fptr, status) > 0)
            return(*status);

    colptr = (fptr->Fptr)->tableptr;
    colptr += (colnum - 1);

    if (colptr->tdatatype >= 0)
        *status = NOT_VARI_LEN;

    bytepos = (fptr->Fptr)->datastart +
                  ((fptr->Fptr)->rowlength * (rownum - 1)) +
                  colptr->tbcol;

    ffmbyt(fptr, bytepos, IGNORE_EOF, status);

    if (colptr->tform[0] == 'P' || colptr->tform[1] == 'P')
    {
        if (length   > UINT_MAX || length   < 0 ||
            heapaddr > UINT_MAX || heapaddr < 0) {
            ffpmsg("P variable length column descriptor is out of range");
	    *status = NUM_OVERFLOW;
            return(*status);
        }

        descript4[0] = (unsigned int) length;
        descript4[1] = (unsigned int) heapaddr;

        ffpi4b(fptr, 2, 4, (INT32BIT *) descript4, status);
    }
    else
    {
        descript8[0] =  length;
        descript8[1] =  heapaddr;

        ffpi8b(fptr, 2, 8, (long *) descript8, status);
    }

    return(*status);
}
