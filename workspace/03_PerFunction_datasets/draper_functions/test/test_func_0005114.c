csv_writerows(WriterObj *self, PyObject *seqseq)
{
    PyObject *row_iter, *row_obj, *result;

    row_iter = PyObject_GetIter(seqseq);
    if (row_iter == NULL) {
        PyErr_SetString(PyExc_TypeError,
                        "writerows() argument must be iterable");
        return NULL;
    }
    while ((row_obj = PyIter_Next(row_iter))) {
        result = csv_writerow(self, row_obj);
        Py_DECREF(row_obj);
        if (!result) {
            Py_DECREF(row_iter);
            return NULL;
        }
        else
             Py_DECREF(result);
    }
    Py_DECREF(row_iter);
    if (PyErr_Occurred())
        return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}
