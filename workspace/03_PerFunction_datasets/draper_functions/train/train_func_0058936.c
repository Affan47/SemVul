binascii_b2a_base64_impl(PyModuleDef *module, Py_buffer *data)

{
    unsigned char *ascii_data, *bin_data;
    int leftbits = 0;
    unsigned char this_ch;
    unsigned int leftchar = 0;
    PyObject *rv;
    Py_ssize_t bin_len;

    bin_data = data->buf;
    bin_len = data->len;

    assert(bin_len >= 0);

    if ( bin_len > BASE64_MAXBIN ) {
        PyErr_SetString(Error, "Too much data for base64 line");
        return NULL;
    }


    if ( (rv=PyBytes_FromStringAndSize(NULL, bin_len*2 + 3)) == NULL )
        return NULL;
    ascii_data = (unsigned char *)PyBytes_AS_STRING(rv);

    for( ; bin_len > 0 ; bin_len--, bin_data++ ) {

        leftchar = (leftchar << 8) | *bin_data;
        leftbits += 8;


        while ( leftbits >= 6 ) {
            this_ch = (leftchar >> (leftbits-6)) & 0x3f;
            leftbits -= 6;
            *ascii_data++ = table_b2a_base64[this_ch];
        }
    }
    if ( leftbits == 2 ) {
        *ascii_data++ = table_b2a_base64[(leftchar&3) << 4];
        *ascii_data++ = BASE64_PAD;
        *ascii_data++ = BASE64_PAD;
    } else if ( leftbits == 4 ) {
        *ascii_data++ = table_b2a_base64[(leftchar&0xf) << 2];
        *ascii_data++ = BASE64_PAD;
    }
    *ascii_data++ = '\n';

    if (_PyBytes_Resize(&rv,
                       (ascii_data -
                        (unsigned char *)PyBytes_AS_STRING(rv))) < 0) {
        Py_CLEAR(rv);
    }
    return rv;
}
