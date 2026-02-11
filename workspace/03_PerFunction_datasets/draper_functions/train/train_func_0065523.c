arrayWrite(const char  *filename,
           const char  *operation,
           void        *data,
           l_int32      nbytes)
{
FILE  *fp;
char   actualOperation[20];

    PROCNAME("arrayWrite");

    if (!filename)
        return ERROR_INT("filename not defined", procName, 1);
    if (!operation)
        return ERROR_INT("operation not defined", procName, 1);
    if (!data)
        return ERROR_INT("data not defined", procName, 1);
    if (nbytes <= 0)
        return ERROR_INT("nbytes must be > 0", procName, 1);

    if (!strcmp(operation, "w") && !strcmp(operation, "a"))
        return ERROR_INT("operation not one of {'w','a'}", procName, 1);

    stringCopy(actualOperation, operation, 2);
    strncat(actualOperation, "b", 2);
    if ((fp = fopen(filename, actualOperation)) == NULL)
        return ERROR_INT("stream not opened", procName, 1);
    fwrite(data, 1, nbytes, fp);
    fclose(fp);

    return 0;
}
