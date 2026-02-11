unicodedata_decomposition(PyObject *self, PyObject *args)
{
    PyUnicodeObject *v;
    char decomp[256];
    int code, index, count, i;
    unsigned int prefix_index;
    Py_UCS4 c;

    if (!PyArg_ParseTuple(args, "O!:decomposition",
                          &PyUnicode_Type, &v))
        return NULL;
    c = getuchar(v);
    if (c == (Py_UCS4)-1)
        return NULL;

    code = (int)c;

    if (self) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0)
            return PyString_FromString("");
    }

    if (code < 0 || code >= 0x110000)
        index = 0;
    else {
        index = decomp_index1[(code>>DECOMP_SHIFT)];
        index = decomp_index2[(index<<DECOMP_SHIFT)+
                             (code&((1<<DECOMP_SHIFT)-1))];
    }


    count = decomp_data[index] >> 8;


    prefix_index = decomp_data[index] & 255;
    assert(prefix_index < (sizeof(decomp_prefix)/sizeof(*decomp_prefix)));


    i = strlen(decomp_prefix[prefix_index]);
    memcpy(decomp, decomp_prefix[prefix_index], i);

    while (count-- > 0) {
        if (i)
            decomp[i++] = ' ';
        assert((size_t)i < sizeof(decomp));
        PyOS_snprintf(decomp + i, sizeof(decomp) - i, "%04X",
                      decomp_data[++index]);
        i += strlen(decomp + i);
    }

    decomp[i] = '\0';

    return PyString_FromString(decomp);
}
