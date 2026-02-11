unicodedata_UCD_decimal_impl(PreviousDBVersion *self, PyUnicodeObject *unichr, PyObject *default_value)

{
    int have_old = 0;
    long rc;
    Py_UCS4 c;

    c = getuchar(unichr);
    if (c == (Py_UCS4)-1)
        return NULL;

    if (self && UCD_Check(self)) {
        const change_record *old = get_old_record(self, c);
        if (old->category_changed == 0) {

            have_old = 1;
            rc = -1;
        }
        else if (old->decimal_changed != 0xFF) {
            have_old = 1;
            rc = old->decimal_changed;
        }
    }

    if (!have_old)
        rc = Py_UNICODE_TODECIMAL(c);
    if (rc < 0) {
        if (default_value == NULL) {
            PyErr_SetString(PyExc_ValueError,
                            "not a decimal");
            return NULL;
        }
        else {
            Py_INCREF(default_value);
            return default_value;
        }
    }
    return PyLong_FromLong(rc);
}
