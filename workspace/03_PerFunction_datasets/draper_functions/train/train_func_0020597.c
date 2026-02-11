tee_setstate(teeobject *to, PyObject *state)
{
    teedataobject *tdo;
    int index;
    if (!PyArg_ParseTuple(state, "O!i", &teedataobject_type, &tdo, &index))
        return NULL;
    if (index < 0 || index > LINKCELLS) {
        PyErr_SetString(PyExc_ValueError, "Index out of range");
        return NULL;
    }
    Py_CLEAR(to->dataobj);
    to->dataobj = tdo;
    Py_INCREF(to->dataobj);
    to->index = index;
    Py_RETURN_NONE;
}
