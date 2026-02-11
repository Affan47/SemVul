ffreopen(fitsfile *openfptr,
             fitsfile **newfptr,
             int *status)


{
    if (*status > 0)
        return(*status);


    if (!openfptr)
        return(*status = NULL_INPUT_PTR);
    else if ((openfptr->Fptr)->validcode != VALIDSTRUC)
        return(*status = BAD_FILEPTR);


    *newfptr = (fitsfile *) calloc(1, sizeof(fitsfile));

    (*newfptr)->Fptr = openfptr->Fptr;
    (*newfptr)->HDUposition = 0;
    (((*newfptr)->Fptr)->open_count)++;

    return(*status);
}
