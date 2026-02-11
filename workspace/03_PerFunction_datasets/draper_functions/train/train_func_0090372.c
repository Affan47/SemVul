ffgkys( fitsfile *fptr,
            const char *keyname,
            char *value,
            char *comm,
            int  *status)


{
    char valstring[FLEN_VALUE];

    if (*status > 0)
        return(*status);

    ffgkey(fptr, keyname, valstring, comm, status);
    value[0] = '\0';
    ffc2s(valstring, value, status);

    return(*status);
}
