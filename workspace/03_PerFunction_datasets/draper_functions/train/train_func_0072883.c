new_timezone(PyObject *offset, PyObject *name)
{
    assert(offset != NULL);
    assert(PyDelta_Check(offset));
    assert(name == NULL || PyUnicode_Check(name));

    if (name == NULL && delta_bool((PyDateTime_Delta *)offset) == 0) {
        Py_INCREF(PyDateTime_TimeZone_UTC);
        return PyDateTime_TimeZone_UTC;
    }
    if (GET_TD_MICROSECONDS(offset) != 0 || GET_TD_SECONDS(offset) % 60 != 0) {
        PyErr_Format(PyExc_ValueError, "offset must be a timedelta"
                     " representing a whole number of minutes,"
                     " not %R.", offset);
        return NULL;
    }
    if ((GET_TD_DAYS(offset) == -1 && GET_TD_SECONDS(offset) == 0) ||
        GET_TD_DAYS(offset) < -1 || GET_TD_DAYS(offset) >= 1) {
        PyErr_Format(PyExc_ValueError, "offset must be a timedelta"
                     " strictly between -timedelta(hours=24) and"
                     " timedelta(hours=24),"
                     " not %R.", offset);
        return NULL;
    }

    return create_timezone(offset, name);
}
