audioop_maxpp(PyObject *self, PyObject *args)
{
    signed char *cp;
    Py_ssize_t len, i;
    int size, val = 0, prevval = 0, prevextremevalid = 0,
        prevextreme = 0;
    int max = 0;
    int diff, prevdiff, extremediff;

    if ( !PyArg_ParseTuple(args, "s#i:maxpp", &cp, &len, &size) )
        return 0;
    if (!audioop_check_parameters(len, size))
        return NULL;


    if ( size == 1 )      prevval = (int)*CHARP(cp, 0);
    else if ( size == 2 ) prevval = (int)*SHORTP(cp, 0);
    else if ( size == 4 ) prevval = (int)*LONGP(cp, 0);
    if ( size == 1 )      val = (int)*CHARP(cp, size);
    else if ( size == 2 ) val = (int)*SHORTP(cp, size);
    else if ( size == 4 ) val = (int)*LONGP(cp, size);
    prevdiff = val - prevval;

    for ( i=size; i<len; i+= size) {
        if ( size == 1 )      val = (int)*CHARP(cp, i);
        else if ( size == 2 ) val = (int)*SHORTP(cp, i);
        else if ( size == 4 ) val = (int)*LONGP(cp, i);
        diff = val - prevval;
        if ( diff*prevdiff < 0 ) {


            if ( prevextremevalid ) {
                extremediff = prevval - prevextreme;
                if ( extremediff < 0 )
                    extremediff = -extremediff;
                if ( extremediff > max )
                    max = extremediff;
            }
            prevextremevalid = 1;
            prevextreme = prevval;
        }
        prevval = val;
        if ( diff != 0 )
            prevdiff = diff;
    }
    return PyLong_FromLong(max);
}
