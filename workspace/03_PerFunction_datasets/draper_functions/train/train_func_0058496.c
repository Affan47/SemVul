binascii_a2b_uu(PyObject *self, PyObject *args)
{
    Py_buffer pascii;
    unsigned char *ascii_data, *bin_data;
    int leftbits = 0;
    unsigned char this_ch;
    unsigned int leftchar = 0;
    PyObject *rv;
    Py_ssize_t ascii_len, bin_len;

    if ( !PyArg_ParseTuple(args, "s*:a2b_uu", &pascii) )
        return NULL;
    ascii_data = pascii.buf;
    ascii_len = pascii.len;

    assert(ascii_len >= 0);


    bin_len = (*ascii_data++ - ' ') & 077;
    ascii_len--;


    if ( (rv=PyString_FromStringAndSize(NULL, bin_len)) == NULL ) {
        PyBuffer_Release(&pascii);
        return NULL;
    }
    bin_data = (unsigned char *)PyString_AS_STRING(rv);

    for( ; bin_len > 0 ; ascii_len--, ascii_data++ ) {

        this_ch = (ascii_len > 0) ? *ascii_data : 0;
        if ( this_ch == '\n' || this_ch == '\r' || ascii_len <= 0) {


            this_ch = 0;
        } else {


            if ( this_ch < ' ' || this_ch > (' ' + 64)) {
                PyErr_SetString(Error, "Illegal char");
                PyBuffer_Release(&pascii);
                Py_DECREF(rv);
                return NULL;
            }
            this_ch = (this_ch - ' ') & 077;
        }


        leftchar = (leftchar << 6) | (this_ch);
        leftbits += 6;
        if ( leftbits >= 8 ) {
            leftbits -= 8;
            *bin_data++ = (leftchar >> leftbits) & 0xff;
            leftchar &= ((1 << leftbits) - 1);
            bin_len--;
        }
    }


    while( ascii_len-- > 0 ) {
        this_ch = *ascii_data++;

        if ( this_ch != ' ' && this_ch != ' '+64 &&
             this_ch != '\n' && this_ch != '\r' ) {
            PyErr_SetString(Error, "Trailing garbage");
            PyBuffer_Release(&pascii);
            Py_DECREF(rv);
            return NULL;
        }
    }
    PyBuffer_Release(&pascii);
    return rv;
}
