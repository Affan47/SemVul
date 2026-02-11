binascii_a2b_base64(PyObject *self, PyObject *args)
{
    Py_buffer pascii;
    unsigned char *ascii_data, *bin_data;
    int leftbits = 0;
    unsigned char this_ch;
    unsigned int leftchar = 0;
    PyObject *rv;
    Py_ssize_t ascii_len, bin_len;
    int quad_pos = 0;

    if ( !PyArg_ParseTuple(args, "s*:a2b_base64", &pascii) )
        return NULL;
    ascii_data = pascii.buf;
    ascii_len = pascii.len;

    assert(ascii_len >= 0);

    if (ascii_len > PY_SSIZE_T_MAX - 3) {
        PyBuffer_Release(&pascii);
        return PyErr_NoMemory();
    }

    bin_len = ((ascii_len+3)/4)*3;


    if ( (rv=PyString_FromStringAndSize(NULL, bin_len)) == NULL ) {
        PyBuffer_Release(&pascii);
        return NULL;
    }
    bin_data = (unsigned char *)PyString_AS_STRING(rv);
    bin_len = 0;

    for( ; ascii_len > 0; ascii_len--, ascii_data++) {
        this_ch = *ascii_data;

        if (this_ch > 0x7f ||
            this_ch == '\r' || this_ch == '\n' || this_ch == ' ')
            continue;


        if (this_ch == BASE64_PAD) {
            if ( (quad_pos < 2) ||
                 ((quad_pos == 2) &&
                  (binascii_find_valid(ascii_data, ascii_len, 1)
                   != BASE64_PAD)) )
            {
                continue;
            }
            else {


                leftbits = 0;
                break;
            }
        }

        this_ch = table_a2b_base64[*ascii_data];
        if ( this_ch == (unsigned char) -1 )
            continue;


        quad_pos = (quad_pos + 1) & 0x03;
        leftchar = (leftchar << 6) | (this_ch);
        leftbits += 6;

        if ( leftbits >= 8 ) {
            leftbits -= 8;
            *bin_data++ = (leftchar >> leftbits) & 0xff;
            bin_len++;
            leftchar &= ((1 << leftbits) - 1);
        }
    }

    if (leftbits != 0) {
        PyBuffer_Release(&pascii);
        PyErr_SetString(Error, "Incorrect padding");
        Py_DECREF(rv);
        return NULL;
    }


    if (bin_len > 0) {
        if (_PyString_Resize(&rv, bin_len) < 0) {
            Py_DECREF(rv);
            rv = NULL;
        }
    }
    else {
        Py_DECREF(rv);
        rv = PyString_FromStringAndSize("", 0);
    }
    PyBuffer_Release(&pascii);
    return rv;
}
