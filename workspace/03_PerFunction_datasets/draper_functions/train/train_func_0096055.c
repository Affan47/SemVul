expand_line_buffer(char **adrBuf, int *ptrSize, char **adrPtr)
{
    char *newbuf;
    int   newsize;

    newsize = *ptrSize + 512;
    newbuf = (char *) malloc(newsize);
    if (newbuf == 0) {
        fprintf(stderr, "Insufficient memory for line");
        exit (EXIT_FAILURE);
    }

    if (*ptrSize == 0) {

        if (adrPtr) {
            *adrPtr = newbuf;
        }
    } else {

        strncpy(newbuf, *adrBuf, *ptrSize);
        if (adrPtr) {
            *adrPtr += newbuf - *adrBuf;
        }
        free(*adrBuf);
    }

    *adrBuf  = newbuf;
    *ptrSize = newsize;

}
