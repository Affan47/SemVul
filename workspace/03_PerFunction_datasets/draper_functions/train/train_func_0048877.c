ffbinr(char **ptr,
                   char *colname,
                   double *minin,
                   double *maxin,
                   double *binsizein,
                   char *minname,
                   char *maxname,
                   char *binname,
                   int *status)


{
    int slen, isanumber;
    char token[FLEN_VALUE];

    if (*status > 0)
        return(*status);

    slen = fits_get_token(ptr, " ,=:;", token, &isanumber);

    if (slen == 0 && (**ptr == '\0' || **ptr == ',' || **ptr == ';') )
        return(*status);

    if (!isanumber && **ptr != ':')
    {


        if (token[0] == '#' && isdigit((int) token[1]) )
        {

            strcpy(colname, token+1);
        }
        else
            strcpy(colname, token);

        while (**ptr == ' ')
             (*ptr)++;

        if (**ptr != '=')
            return(*status);

        (*ptr)++;

        while (**ptr == ' ')
             (*ptr)++;

        slen = fits_get_token(ptr, " ,:;", token, &isanumber);
    }

    if (**ptr != ':')
    {


        if (!isanumber)
            strcpy(binname, token);
        else
            *binsizein =  strtod(token, NULL);

        return(*status);
    }
    else
    {

        if (slen)
        {
            if (!isanumber)
                strcpy(minname, token);
            else
                *minin = strtod(token, NULL);
        }
    }

    (*ptr)++;
    slen = fits_get_token(ptr, " ,:;", token, &isanumber);


    if (slen)
    {
        if (!isanumber)
            strcpy(maxname, token);
        else
            *maxin = strtod(token, NULL);
    }

    if (**ptr != ':')
        return(*status);

    (*ptr)++;
    slen = fits_get_token(ptr, " ,:;", token, &isanumber);


    if (slen)
    {
        if (!isanumber)
            strcpy(binname, token);
        else
            *binsizein = strtod(token, NULL);
    }

    return(*status);
}
