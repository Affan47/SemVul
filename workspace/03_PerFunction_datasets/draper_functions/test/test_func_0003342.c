ffgcfc(fitsfile *fptr,
           int  colnum,
           LONGLONG  firstrow,
           LONGLONG  firstelem,
           LONGLONG  nelem,
           float *array,
           char *nularray,
           int  *anynul,
           int  *status)


{
    long ii, jj;
    float dummy = 0;
    char *carray;


    carray = (char *) calloc( (size_t) (nelem * 2), 1);

    ffgcle(fptr, colnum, firstrow, (firstelem - 1) * 2 + 1, nelem * 2,
           1, 2, dummy, array, carray, anynul, status);

    for (ii = 0, jj = 0; jj < nelem; ii += 2, jj++)
    {
       if (carray[ii] || carray[ii + 1])
          nularray[jj] = 1;
       else
          nularray[jj] = 0;
    }

    free(carray);
    return(*status);
}
