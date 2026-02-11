audioop_adpcm2lin(PyObject *self, PyObject *args)
{
    signed char *cp;
    signed char *ncp;
    Py_ssize_t len, i;
    int size, valpred, step, delta, index, sign, vpdiff;
    PyObject *rv, *str, *state;
    int inputbuffer = 0, bufferstep;

    if ( !PyArg_ParseTuple(args, "s#iO:adpcm2lin",
                           &cp, &len, &size, &state) )
        return 0;

    if (!audioop_check_size(size))
        return NULL;


    if ( state == Py_None ) {

        valpred = 0;
        index = 0;
    } else if ( !PyArg_ParseTuple(state, "ii", &valpred, &index) )
        return 0;

    if (len > (PY_SSIZE_T_MAX/2)/size) {
        PyErr_SetString(PyExc_MemoryError,
                        "not enough memory for output buffer");
        return 0;
    }
    str = PyBytes_FromStringAndSize(NULL, len*size*2);
    if ( str == 0 )
        return 0;
    ncp = (signed char *)PyBytes_AsString(str);

    step = stepsizeTable[index];
    bufferstep = 0;

    for ( i=0; i < len*size*2; i += size ) {

        if ( bufferstep ) {
            delta = inputbuffer & 0xf;
        } else {
            inputbuffer = *cp++;
            delta = (inputbuffer >> 4) & 0xf;
        }

        bufferstep = !bufferstep;


        index += indexTable[delta];
        if ( index < 0 ) index = 0;
        if ( index > 88 ) index = 88;


        sign = delta & 8;
        delta = delta & 7;


        vpdiff = step >> 3;
        if ( delta & 4 ) vpdiff += step;
        if ( delta & 2 ) vpdiff += step>>1;
        if ( delta & 1 ) vpdiff += step>>2;

        if ( sign )
            valpred -= vpdiff;
        else
            valpred += vpdiff;


        if ( valpred > 32767 )
            valpred = 32767;
        else if ( valpred < -32768 )
            valpred = -32768;


        step = stepsizeTable[index];


        if ( size == 1 ) *CHARP(ncp, i) = (signed char)(valpred >> 8);
        else if ( size == 2 ) *SHORTP(ncp, i) = (short)(valpred);
        else if ( size == 4 ) *LONGP(ncp, i) = (Py_Int32)(valpred<<16);
    }

    rv = Py_BuildValue("(O(ii))", str, valpred, index);
    Py_DECREF(str);
    return rv;
}
