datetime_subtract(PyObject *left, PyObject *right)
{
    PyObject *result = Py_NotImplemented;

    if (PyDateTime_Check(left)) {

        if (PyDateTime_Check(right)) {

            PyObject *offset1, *offset2, *offdiff = NULL;
            int delta_d, delta_s, delta_us;

            if (GET_DT_TZINFO(left) == GET_DT_TZINFO(right)) {
                offset2 = offset1 = Py_None;
                Py_INCREF(offset1);
                Py_INCREF(offset2);
            }
            else {
                offset1 = datetime_utcoffset(left, NULL);
                if (offset1 == NULL)
                    return NULL;
                offset2 = datetime_utcoffset(right, NULL);
                if (offset2 == NULL) {
                    Py_DECREF(offset1);
                    return NULL;
                }
                if ((offset1 != Py_None) != (offset2 != Py_None)) {
                    PyErr_SetString(PyExc_TypeError,
                                    "can't subtract offset-naive and "
                                    "offset-aware datetimes");
                    Py_DECREF(offset1);
                    Py_DECREF(offset2);
                    return NULL;
                }
            }
            if ((offset1 != offset2) &&
                delta_cmp(offset1, offset2) != 0) {
                offdiff = delta_subtract(offset1, offset2);
                if (offdiff == NULL) {
                    Py_DECREF(offset1);
                    Py_DECREF(offset2);
                    return NULL;
                }
            }
            Py_DECREF(offset1);
            Py_DECREF(offset2);
            delta_d = ymd_to_ord(GET_YEAR(left),
                                 GET_MONTH(left),
                                 GET_DAY(left)) -
                      ymd_to_ord(GET_YEAR(right),
                                 GET_MONTH(right),
                                 GET_DAY(right));


            delta_s = (DATE_GET_HOUR(left) -
                       DATE_GET_HOUR(right)) * 3600 +
                      (DATE_GET_MINUTE(left) -
                       DATE_GET_MINUTE(right)) * 60 +
                      (DATE_GET_SECOND(left) -
                       DATE_GET_SECOND(right));
            delta_us = DATE_GET_MICROSECOND(left) -
                       DATE_GET_MICROSECOND(right);
            result = new_delta(delta_d, delta_s, delta_us, 1);
            if (offdiff != NULL) {
                PyObject *temp = result;
                result = delta_subtract(result, offdiff);
                Py_DECREF(temp);
                Py_DECREF(offdiff);
            }
        }
        else if (PyDelta_Check(right)) {

            result = add_datetime_timedelta(
                            (PyDateTime_DateTime *)left,
                            (PyDateTime_Delta *)right,
                            -1);
        }
    }

    if (result == Py_NotImplemented)
        Py_INCREF(result);
    return result;
}
