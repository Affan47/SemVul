ffppr(  fitsfile *fptr,
            int  datatype,
            LONGLONG  firstelem,
            LONGLONG  nelem,
            void  *array,
            int  *status)


{
    long group = 1;

    if (*status > 0)
        return(*status);

    if (datatype == TBYTE)
    {
      ffpprb(fptr, group, firstelem, nelem, (unsigned char *) array, status);
    }
    else if (datatype == TSBYTE)
    {
      ffpprsb(fptr, group, firstelem, nelem, (signed char *) array, status);
    }
    else if (datatype == TUSHORT)
    {
      ffpprui(fptr, group, firstelem, nelem, (unsigned short *) array,
              status);
    }
    else if (datatype == TSHORT)
    {
      ffppri(fptr, group, firstelem, nelem, (short *) array, status);
    }
    else if (datatype == TUINT)
    {
      ffppruk(fptr, group, firstelem, nelem, (unsigned int *) array, status);
    }
    else if (datatype == TINT)
    {
      ffpprk(fptr, group, firstelem, nelem, (int *) array, status);
    }
    else if (datatype == TULONG)
    {
      ffppruj(fptr, group, firstelem, nelem, (unsigned long *) array, status);
    }
    else if (datatype == TLONG)
    {
      ffpprj(fptr, group, firstelem, nelem, (long *) array, status);
    }
    else if (datatype == TLONGLONG)
    {
      ffpprjj(fptr, group, firstelem, nelem, (LONGLONG *) array, status);
    }
    else if (datatype == TFLOAT)
    {
      ffppre(fptr, group, firstelem, nelem, (float *) array, status);
    }
    else if (datatype == TDOUBLE)
    {
      ffpprd(fptr, group, firstelem, nelem, (double *) array, status);
    }
    else
      *status = BAD_DATATYPE;

    return(*status);
}
