audioop_lin2ulaw(PyObject *self, PyObject *args)
{
    signed char *cp;
    unsigned char *ncp;
    Py_ssize_t len, i;
    int size, val = 0;
    PyObject *rv;

    if ( !PyArg_ParseTuple(args, "s#i:lin2ulaw",
                           &cp, &len, &size) )
        return 0 ;

    if (!audioop_check_parameters(len, size))
        return NULL;

    rv = PyBytes_FromStringAndSize(NULL, len/size);
    if ( rv == 0 )
        return 0;
    ncp = (unsigned char *)PyBytes_AsString(rv);

    for ( i=0; i < len; i += size ) {
        if ( size == 1 )      val = ((int)*CHARP(cp, i)) << 8;
        else if ( size == 2 ) val = (int)*SHORTP(cp, i);
        else if ( size == 4 ) val = ((int)*LONGP(cp, i)) >> 16;

        *ncp++ = st_14linear2ulaw(val);
    }
    return rv;
}
