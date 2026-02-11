tmtotuple(struct tm *p)
{
    PyObject *v = PyStructSequence_New(&StructTimeType);
    if (v == NULL)
        return NULL;

#define SET(i,val) PyStructSequence_SET_ITEM(v, i, PyLong_FromLong((long) val))

    SET(0, p->tm_year + 1900);
    SET(1, p->tm_mon + 1);
    SET(2, p->tm_mday);
    SET(3, p->tm_hour);
    SET(4, p->tm_min);
    SET(5, p->tm_sec);
    SET(6, (p->tm_wday + 6) % 7);
    SET(7, p->tm_yday + 1);
    SET(8, p->tm_isdst);
#undef SET
    if (PyErr_Occurred()) {
        Py_XDECREF(v);
        return NULL;
    }

    return v;
}
