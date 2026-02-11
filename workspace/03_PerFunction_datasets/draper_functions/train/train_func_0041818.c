ffgkym( fitsfile *fptr,
            const char  *keyname,
            double *value,
            char  *comm,
            int   *status)


{
    char valstring[FLEN_VALUE], message[81];
    int len;

    if (*status > 0)
        return(*status);

    ffgkey(fptr, keyname, valstring, comm, status);

    if (valstring[0] != '(' )
    {
      sprintf(message, "keyword %s does not have a complex value (ffgkym):",
              keyname);
      ffpmsg(message);
      ffpmsg(valstring);
      return(*status = BAD_C2D);
    }

    valstring[0] = ' ';
    len = strcspn(valstring, ")" );
    valstring[len] = '\0';

    len = strcspn(valstring, ",");
    valstring[len] = '\0';

    ffc2d(valstring, &value[0], status);
    ffc2d(&valstring[len + 1], &value[1], status);

    return(*status);
}
