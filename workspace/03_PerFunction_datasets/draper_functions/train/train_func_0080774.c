PyDec_Round(PyObject *dec, PyObject *args)
{
    PyObject *result;
    PyObject *x = NULL;
    uint32_t status = 0;
    PyObject *context;


    CURRENT_CONTEXT(context);
    if (!PyArg_ParseTuple(args, "|O", &x)) {
        return NULL;
    }

    if (x) {
        mpd_uint_t dq[1] = {1};
        mpd_t q = {MPD_STATIC|MPD_CONST_DATA,0,1,1,1,dq};
        mpd_ssize_t y;

        if (!PyLong_Check(x)) {
            PyErr_SetString(PyExc_TypeError,
                "optional arg must be an integer");
            return NULL;
        }

        y = PyLong_AsSsize_t(x);
        if (y == -1 && PyErr_Occurred()) {
            return NULL;
        }
        result = dec_alloc();
        if (result == NULL) {
            return NULL;
        }

        q.exp = (y == MPD_SSIZE_MIN) ? MPD_SSIZE_MAX : -y;
        mpd_qquantize(MPD(result), MPD(dec), &q, CTX(context), &status);
        if (dec_addstatus(context, status)) {
            Py_DECREF(result);
            return NULL;
        }

        return result;
    }
    else {
        return dec_as_long(dec, context, MPD_ROUND_HALF_EVEN);
    }
}
